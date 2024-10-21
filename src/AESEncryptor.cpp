#include "AESEncryptor.h"
#include <openssl/aes.h>
#include <openssl/rand.h>
#include <fstream>
#include <stdexcept>
#include <vector>
#include <cstring>

void AESEncryptor::generateRandomKey() {
    if (!RAND_bytes(key, sizeof(key))) {
        throw std::runtime_error("Failed to generate random key");
    }
}

void AESEncryptor::encrypt(const unsigned char *plaintext, unsigned char *ciphertext) {
    AES_KEY enc_key;
    AES_set_encrypt_key(key, 128, &enc_key);
    AES_encrypt(plaintext, ciphertext, &enc_key);
}

void AESEncryptor::decrypt(const unsigned char *ciphertext, unsigned char *plaintext) {
    AES_KEY dec_key;
    AES_set_decrypt_key(key, 128, &dec_key);
    AES_decrypt(ciphertext, plaintext, &dec_key);
}

void AESEncryptor::encryptFile(const std::string &inputFileName, const std::string &outputFileName) {
    generateRandomKey();

    std::ifstream inputFile(inputFileName, std::ios::binary);
    std::ofstream outputFile(outputFileName, std::ios::binary);
    if (!inputFile.is_open() || !outputFile.is_open()) {
        throw std::runtime_error("Could not open file");
    }

    unsigned char buffer[16];
    while (inputFile.read(reinterpret_cast<char *>(buffer), sizeof(buffer)) || inputFile.gcount() > 0) {
        size_t bytesRead = inputFile.gcount();
        if (bytesRead < 16) {
            std::memset(buffer + bytesRead, 0, 16 - bytesRead); // Zero padding
        }
        unsigned char ciphertext[16];
        encrypt(buffer, ciphertext);
        outputFile.write(reinterpret_cast<char *>(ciphertext), sizeof(ciphertext));
    }
}

void AESEncryptor::decryptFile(const std::string &inputFileName, const std::string &outputFileName) {
    std::ifstream inputFile(inputFileName, std::ios::binary);
    std::ofstream outputFile(outputFileName, std::ios::binary);
    if (!inputFile.is_open() || !outputFile.is_open()) {
        throw std::runtime_error("Could not open file");
    }

    unsigned char buffer[16];
    while (inputFile.read(reinterpret_cast<char *>(buffer), sizeof(buffer))) {
        unsigned char plaintext[16];
        decrypt(buffer, plaintext);
        outputFile.write(reinterpret_cast<char *>(plaintext), sizeof(plaintext));
    }
}
