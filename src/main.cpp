#include "CryptoManager.h"
#include <iostream>

int main() {
    CryptoManager cryptoManager;
    
    std::string inputFileName = "input.txt";  // 输入文件
    std::string encryptedFileName = "encrypted.dat";
    std::string decryptedFileName = "decrypted.txt";

    try {
        // Encrypt using AES
        cryptoManager.encryptFile(inputFileName, encryptedFileName, CryptoManager::AES);
        std::cout << "File encrypted (AES): " << encryptedFileName << std::endl;

        // Decrypt using AES
        cryptoManager.decryptFile(encryptedFileName, decryptedFileName, CryptoManager::AES);
        std::cout << "File decrypted (AES): " << decryptedFileName << std::endl;

        // Generate HMAC
        std::string hmac;
        cryptoManager.generateHMAC("Sample data for HMAC", hmac);
        std::cout << "Generated HMAC: " << hmac << std::endl;

        // Encrypt using DES
        cryptoManager.encryptFile(inputFileName, "encrypted_des.dat", CryptoManager::DES);
        std::cout << "File encrypted (DES): encrypted_des.dat" << std::endl;

        // Decrypt using DES
        cryptoManager.decryptFile("encrypted_des.dat", "decrypted_des.txt", CryptoManager::DES);
        std::cout << "File decrypted (DES): decrypted_des.txt" << std::endl;

    } catch (const std::exception &e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
    }

    return 0;
}
