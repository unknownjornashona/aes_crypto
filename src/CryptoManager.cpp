#include "CryptoManager.h"
#include <stdexcept>

void CryptoManager::encryptFile(const std::string &inputFileName, const std::string &outputFileName, Algorithm algo) {
    switch (algo) {
        case AES:
            aesEncryptor.encryptFile(inputFileName, outputFileName);
            break;
        case DES:
            desEncryptor.encryptFile(inputFileName, outputFileName);
            break;
        default:
            throw std::invalid_argument("Unsupported encryption algorithm.");
    }
}

void CryptoManager::decryptFile(const std::string &inputFileName, const std::string &outputFileName, Algorithm algo) {
    switch (algo) {
        case AES:
            aesEncryptor.decryptFile(inputFileName, outputFileName);
            break;
        case DES:
            desEncryptor.decryptFile(inputFileName, outputFileName);
            break;
        default:
            throw std::invalid_argument("Unsupported decryption algorithm.");
    }
}

void CryptoManager::generateHMAC(const std::string &data, std::string &hmac) {
    hmacGenerator.generateHMAC(data, hmac);
}
