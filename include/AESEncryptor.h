#ifndef AESEnCRYPTOR_H
#define AESENCRYPTOR_H

#include <string>

class AESEncryptor {
public:
    void encryptFile(const std::string &inputFileName, const std::string &outputFileName);
    void decryptFile(const std::string &inputFileName, const std::string &outputFileName);

private:
    unsigned char key[16]; // 128-bit AES key
    void generateRandomKey();
    void encrypt(const unsigned char *plaintext, unsigned char *ciphertext);
    void decrypt(const unsigned char *ciphertext, unsigned char *plaintext);
};

#endif // AESEnCRYPTOR_H
