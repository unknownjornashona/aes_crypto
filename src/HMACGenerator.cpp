#include "HMACGenerator.h"
#include <openssl/hmac.h>

void HMACGenerator::generateHMAC(const std::string &data, std::string &hmac) {
    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int length = 0;
    const char *key = "secret"; // 这里可以是动态输入的密钥

    HMAC(EVP_sha256(), key, strlen(key), reinterpret_cast<const unsigned char *>(data.c_str()), data.size(), hash, &length);
    hmac.assign(reinterpret_cast<char *>(hash), length);
}
