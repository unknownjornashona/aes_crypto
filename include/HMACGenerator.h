#ifndef HMACGENERATOR_H
#define HMACGENERATOR_H

#include <string>

class HMACGenerator {
public:
    void generateHMAC(const std::string &data, std::string &hmac);
};

#endif // HMACGENERATOR_H
