#ifdef ENABLE_CRYPTO_HANDLER

#include "CryptoHandler.h"
#include "Globals.h"
#include "mbedtls/base64.h"
#include "mbedtls/md.h"
#include "mbedtls/aes.h"
#include "CommandHandler.h"

#define AES_KEY_SIZE 32   // AES-256 key size (256 bits)
#define AES_BLOCK_SIZE 16 // Block size for AES CBC mode

// Derive a 32-byte key from a password using SHA-256
void deriveKey(const String &password, uint8_t *keyOut)
{
    mbedtls_md_context_t ctx;
    mbedtls_md_init(&ctx);
    mbedtls_md_setup(&ctx, mbedtls_md_info_from_type(MBEDTLS_MD_SHA256), 0);
    mbedtls_md_starts(&ctx);
    mbedtls_md_update(&ctx, (const uint8_t *)password.c_str(), password.length());
    mbedtls_md_finish(&ctx, keyOut);
    mbedtls_md_free(&ctx);
}

String CryptoHandler::encryptAES(const String &plainText, const String &password)
{
    uint8_t aesKey[AES_KEY_SIZE];
    deriveKey(password, aesKey); // Hash the password to get the 32-byte key

    uint8_t iv[AES_BLOCK_SIZE];
    esp_fill_random(iv, AES_BLOCK_SIZE); // Generate a random IV

    size_t inputLen = plainText.length();
    size_t paddedLen = ((inputLen / AES_BLOCK_SIZE) + 1) * AES_BLOCK_SIZE;
    uint8_t *input = (uint8_t *)calloc(paddedLen, 1);
    memcpy(input, plainText.c_str(), inputLen);

    // Apply Pkcs7 padding
    uint8_t padVal = AES_BLOCK_SIZE - (inputLen % AES_BLOCK_SIZE);
    for (size_t i = inputLen; i < paddedLen; i++) {
        input[i] = padVal;
    }

    uint8_t *output = (uint8_t *)calloc(paddedLen, 1);

    mbedtls_aes_context aes;
    mbedtls_aes_init(&aes);
    mbedtls_aes_setkey_enc(&aes, aesKey, AES_KEY_SIZE * 8);
    mbedtls_aes_crypt_cbc(&aes, MBEDTLS_AES_ENCRYPT, paddedLen, iv, input, output);
    mbedtls_aes_free(&aes);

    // Prepend IV to ciphertext
    uint8_t finalOutput[AES_BLOCK_SIZE + paddedLen];
    memcpy(finalOutput, iv, AES_BLOCK_SIZE);
    memcpy(finalOutput + AES_BLOCK_SIZE, output, paddedLen);

    // Base64 encode
    size_t base64Len;
    uint8_t base64Output[128];
    mbedtls_base64_encode(base64Output, sizeof(base64Output), &base64Len, finalOutput, sizeof(finalOutput));

    free(input);
    free(output);

    return String((char *)base64Output);
}

String CryptoHandler::decryptAES(const String &cipherText, const String &password)
{
    uint8_t aesKey[AES_KEY_SIZE];
    deriveKey(password, aesKey); // Hash the password to get the 32-byte key

    uint8_t decoded[128];
    size_t decodedLen;
    mbedtls_base64_decode(decoded, sizeof(decoded), &decodedLen, (const uint8_t *)cipherText.c_str(), cipherText.length());

    if (decodedLen < AES_BLOCK_SIZE)
    {
        debugE("Invalid ciphertext");
        return "";
    }

    uint8_t iv[AES_BLOCK_SIZE];
    memcpy(iv, decoded, AES_BLOCK_SIZE); // Extract IV from first 16 bytes
    uint8_t *ciphertext = decoded + AES_BLOCK_SIZE;
    size_t cipherLen = decodedLen - AES_BLOCK_SIZE;

    uint8_t *output = (uint8_t *)calloc(cipherLen, 1);

    mbedtls_aes_context aes;
    mbedtls_aes_init(&aes);
    mbedtls_aes_setkey_dec(&aes, aesKey, AES_KEY_SIZE * 8);
    mbedtls_aes_crypt_cbc(&aes, MBEDTLS_AES_DECRYPT, cipherLen, iv, ciphertext, output);
    mbedtls_aes_free(&aes);

    // Remove Pkcs7 padding
    uint8_t padVal = output[cipherLen - 1];
    if (padVal > 0 && padVal <= AES_BLOCK_SIZE)
    {
        cipherLen -= padVal;
    }

    String decryptedText = String((char *)output).substring(0, cipherLen);
    free(output);
    return decryptedText;
}

void CryptoHandler::init()
{
        CommandHandler::registerCommand("CRYPTO", [](const String &command)
                                    {
        String cmd, args;
        CommandHandler::parseCommand(command, cmd, args);

        if (CommandHandler::equalsIgnoreCase(cmd, "ENCRYPT")) {
            int spaceIndex = args.indexOf(' ');
            if (spaceIndex > 0) {
                String key = args.substring(0, spaceIndex);
                String text = args.substring(spaceIndex + 1);
                String encrypted = encryptAES(text, key);
                debugI("Encrypted: %s", encrypted.c_str());
            } else {
                debugW("Usage: CRYPTO ENCRYPT <key> <text>");
            }
        } else if (CommandHandler::equalsIgnoreCase(cmd, "DECRYPT")) {
            int spaceIndex = args.indexOf(' ');
            if (spaceIndex > 0) {
                String key = args.substring(0, spaceIndex);
                String text = args.substring(spaceIndex + 1);
                String decrypted = decryptAES(text, key);
                debugI("Decrypted: %s", decrypted.c_str());
            } else {
                debugW("Usage: CRYPTO DECRYPT <key> <ciphertext>");
            }
        } else {
            debugW("Unknown CRYPTO subcommand: %s", cmd.c_str());
        } }, "Handles CRYPTO commands. Usage: CRYPTO <subcommand> <args>\n"
             "  Subcommands:\n"
             "  encrypt <key> <text> - Encrypts a string\n"
             "  decrypt <key> <ciphertext> - Decrypts a string");
    
    debugI("CryptoHandler initialized");
}

#endif // ENABLE_CRYPTO_HANDLER
