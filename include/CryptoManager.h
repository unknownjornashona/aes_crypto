#ifndef CRYPTOMANAGER_H
#define CRYPTOMANAGER_H

#include <string>
#include "AESEncryptor.h"
#include "DESEncryptor.h"
#include "HMACGenerator.h"

class CryptoManager {
public:
    enum Algorithm {
        AES,
        DES
    };

    void encryptFile(const std::string &inputFileName, const std::string &outputFileName, Algorithm algo);
    void decryptFile(const std::string &inputFileName, const std::string &outputFileName, Algorithm algo);
    void generateHMAC(const std::string &data, std::string &hmac);

private:
    AESEncryptor aesEncryptor;
    DESEncryptor desEncryptor;
    HMACGenerator hmacGenerator;
};

#endif // CRYPTOMANAGER_H
