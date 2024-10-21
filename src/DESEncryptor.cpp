#include "DESEncryptor.h"
#include <openssl/des.h>
#include <openssl/rand.h>
#include <fstream>
#include <stdexcept>
#include <vector>
#include <cstring>

void DESEncryptor::generateRandomKey() {
    if (!RAND_bytes(key, sizeof(key))) {
        throw std::runtime_error("Failed to generate random key");
    }
}

void DESEncryptor::encrypt(const unsigned char *plaintext, unsigned char *ciphertext) {
    DES_key_schedule key_schedule;
    DES_set_key_unchecked((DES_cblock *)key, &key_schedule);
    DES_ecb_encrypt((DES_cblock *)plaintext, (DES_cblock *)ciphertext, &key_schedule, DES_ENCRYPT);
}

void DESEncryptor::decrypt(const unsigned char *ciphertext, unsigned char *plaintext) {
    DES_key_schedule key_schedule;
    DES_set_key_unchecked((DES_cblock *)key, &key_schedule);
    DES_ecb_encrypt((DES_cblock *)ciphertext, (DES_cblock *)plaintext, &key_schedule, DES_DECRYPT);
}

void DESEncryptor::encryptFile(const std::string &inputFileName, const std::string &outputFileName) {
    generateRandomKey();

    std::ifstream inputFile(inputFileName, std::ios::binary);
    std::ofstream outputFile(outputFileName, std::ios::binary);
    if (!inputFile.is_open() || !outputFile.is_open()) {
        throw std::runtime_error("Could not open file");
    }

    unsigned char buffer[8];
    while (inputFile.read(reinterpret_cast<char *>(buffer), sizeof(buffer)) || inputFile.gcount() > 0) {
        size_t bytesRead = inputFile.gcount();
        if (bytesRead < 8) {
            std::memset(buffer + bytesRead, 0, 8 - bytesRead); // Zero padding
        }
        unsigned char ciphertext[8];
        encrypt(buffer, ciphertext);
        outputFile.write(reinterpret_cast<char *>(ciphertext), sizeof(ciphertext));
    }
}

void DESEncryptor::decryptFile(const std::string &inputFileName, const std::string &outputFileName) {
    std::ifstream inputFile(inputFileName, std::ios::binary);
    std::ofstream outputFile(outputFileName, std::ios::binary);
    if (!inputFile.is_open() || !outputFile.is_open()) {
        throw std::runtime_error("Could not open file");
    }

    unsigned char buffer[8];
    while (inputFile.read(reinterpret_cast<char *>(buffer), sizeof(buffer))) {
        unsigned char plaintext[8];
        decrypt(buffer, plaintext);
        outputFile.write(reinterpret_cast<char *>(plaintext), sizeof(plaintext));
    }
}
