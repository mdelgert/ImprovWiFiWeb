#ifdef ENABLE_CRYPTO_HANDLER

#include "CryptoHandler.h"
#include "Globals.h"
#include "mbedtls/base64.h"
#include "mbedtls/md.h"
#include "mbedtls/aes.h"
#include "CommandHandler.h"

#define AES_KEY_SIZE 32  // AES-256 requires a 32-byte key
#define AES_BLOCK_SIZE 16

String CryptoHandler::encryptAES(const String &plainText, const String &key)
{
    if (key.length() < AES_KEY_SIZE)
    {
        debugE("Encryption key must be at least %d bytes long.", AES_KEY_SIZE);
        return "";
    }

    uint8_t aesKey[AES_KEY_SIZE];
    memcpy(aesKey, key.c_str(), AES_KEY_SIZE);

    uint8_t iv[AES_BLOCK_SIZE] = {0}; // Initialization vector (set to zero)
    uint8_t input[plainText.length() + AES_BLOCK_SIZE];
    uint8_t output[plainText.length() + AES_BLOCK_SIZE];

    memset(input, 0, sizeof(input));
    memcpy(input, plainText.c_str(), plainText.length());

    mbedtls_aes_context aes;
    mbedtls_aes_init(&aes);
    mbedtls_aes_setkey_enc(&aes, aesKey, AES_KEY_SIZE * 8);
    mbedtls_aes_crypt_cbc(&aes, MBEDTLS_AES_ENCRYPT, sizeof(input), iv, input, output);
    mbedtls_aes_free(&aes);

    size_t base64Len;
    uint8_t base64Output[64];
    mbedtls_base64_encode(base64Output, sizeof(base64Output), &base64Len, output, sizeof(output));

    return String((char *)base64Output);
}

String CryptoHandler::decryptAES(const String &cipherText, const String &key)
{
    if (key.length() < AES_KEY_SIZE)
    {
        debugE("Decryption key must be at least %d bytes long.", AES_KEY_SIZE);
        return "";
    }

    uint8_t aesKey[AES_KEY_SIZE];
    memcpy(aesKey, key.c_str(), AES_KEY_SIZE);

    uint8_t iv[AES_BLOCK_SIZE] = {0}; // Initialization vector (set to zero)
    uint8_t encryptedData[64];
    uint8_t decryptedOutput[64];

    size_t decodedLen;
    mbedtls_base64_decode(encryptedData, sizeof(encryptedData), &decodedLen, (const uint8_t *)cipherText.c_str(), cipherText.length());

    mbedtls_aes_context aes;
    mbedtls_aes_init(&aes);
    mbedtls_aes_setkey_dec(&aes, aesKey, AES_KEY_SIZE * 8);
    mbedtls_aes_crypt_cbc(&aes, MBEDTLS_AES_DECRYPT, decodedLen, iv, encryptedData, decryptedOutput);
    mbedtls_aes_free(&aes);

    return String((char *)decryptedOutput);
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
