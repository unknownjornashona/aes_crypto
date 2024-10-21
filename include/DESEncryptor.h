#ifndef DESEnCRYPTOR_H
#define DESENCRYPTOR_H

#include <string>

class DESEncryptor {
public:
    void encryptFile(const std::string &inputFileName, const std::string &outputFileName);
    void decryptFile(const std::string &inputFileName, const std::string &outputFileName);

private:
    unsigned char key[8]; // 64-bit DES key
    void generateRandomKey();
    void encrypt(const unsigned char *plaintext, unsigned char *ciphertext);
    void decrypt(const unsigned char *ciphertext, unsigned char *plaintext);
};

#endif // DESEnCRYPTOR_H
