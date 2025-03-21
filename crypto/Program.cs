using System;
using System.Security.Cryptography;
using System.Text;

class Program
{
    private const int AesKeySize = 32; // 256 bits
    private const int AesBlockSize = 16; // 128 bits

    static void Main(string[] args)
    {
        if (args.Length < 3)
        {
            Console.WriteLine("Usage: dotnet run <enc|dec> <text> <password>");
            //Console.WriteLine("Usage: crypto <enc|dec> <text> <password>");
            return;
        }

        string command = args[0].ToLower();
        string text = args[1];
        string password = args[2];

        try
        {
            if (command == "enc")
            {
                string encrypted = Encrypt(text, password);
                Console.WriteLine($"Encrypted: {encrypted}");
            }
            else if (command == "dec")
            {
                string decrypted = Decrypt(text, password);
                Console.WriteLine($"Decrypted: {decrypted}");
            }
            else
            {
                Console.WriteLine("Invalid command. Use 'encrypt' or 'decrypt'.");
            }
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Error: {ex.Message}");
        }
    }

    static string Encrypt(string plainText, string password)
    {
        // Derive 32-byte key using SHA-256
        byte[] key = ComputeSha256Hash(password);

        // Generate random 16-byte IV
        byte[] iv = GenerateRandomBytes(AesBlockSize);

        // Encrypt using AES-CBC with PKCS7 padding
        byte[] cipherText;
        using (Aes aes = Aes.Create())
        {
            aes.KeySize = AesKeySize * 8;
            aes.BlockSize = AesBlockSize * 8;
            aes.Mode = CipherMode.CBC;
            aes.Padding = PaddingMode.PKCS7;
            aes.Key = key;
            aes.IV = iv;

            using (ICryptoTransform encryptor = aes.CreateEncryptor())
            {
                byte[] plainBytes = Encoding.UTF8.GetBytes(plainText);
                cipherText = encryptor.TransformFinalBlock(plainBytes, 0, plainBytes.Length);
            }
        }

        // Prepend IV to ciphertext
        byte[] finalOutput = new byte[AesBlockSize + cipherText.Length];
        Array.Copy(iv, 0, finalOutput, 0, AesBlockSize);
        Array.Copy(cipherText, 0, finalOutput, AesBlockSize, cipherText.Length);

        // Base64 encode
        return Convert.ToBase64String(finalOutput);
    }

    static string Decrypt(string encryptedBase64, string password)
    {
        // Derive 32-byte key using SHA-256
        byte[] key = ComputeSha256Hash(password);

        // Decode Base64
        byte[] encryptedBytes = Convert.FromBase64String(encryptedBase64);
        if (encryptedBytes.Length < AesBlockSize)
        {
            throw new ArgumentException("Invalid encrypted data: too short.");
        }

        // Extract IV (first 16 bytes) and ciphertext
        byte[] iv = new byte[AesBlockSize];
        byte[] cipherText = new byte[encryptedBytes.Length - AesBlockSize];
        Array.Copy(encryptedBytes, 0, iv, 0, AesBlockSize);
        Array.Copy(encryptedBytes, AesBlockSize, cipherText, 0, cipherText.Length);

        // Decrypt using AES-CBC with PKCS7 padding
        byte[] plainBytes;
        using (Aes aes = Aes.Create())
        {
            aes.KeySize = AesKeySize * 8;
            aes.BlockSize = AesBlockSize * 8;
            aes.Mode = CipherMode.CBC;
            aes.Padding = PaddingMode.PKCS7;
            aes.Key = key;
            aes.IV = iv;

            using (ICryptoTransform decryptor = aes.CreateDecryptor())
            {
                plainBytes = decryptor.TransformFinalBlock(cipherText, 0, cipherText.Length);
            }
        }

        return Encoding.UTF8.GetString(plainBytes);
    }

    static byte[] ComputeSha256Hash(string input)
    {
        using (SHA256 sha256 = SHA256.Create())
        {
            return sha256.ComputeHash(Encoding.UTF8.GetBytes(input));
        }
    }

    static byte[] GenerateRandomBytes(int length)
    {
        byte[] randomBytes = new byte[length];
        using (RandomNumberGenerator rng = RandomNumberGenerator.Create())
        {
            rng.GetBytes(randomBytes);
        }
        return randomBytes;
    }
}