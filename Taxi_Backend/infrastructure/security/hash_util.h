#ifndef HASH_UTIL_H
#define HASH_UTIL_H

#include "../../lib/lib.h"

class HashUtil {
public:
    static string hashPassword(const string& password) {
        unsigned char hash[SHA256_DIGEST_LENGTH];
        SHA256(reinterpret_cast<const unsigned char*>(password.c_str()), password.size(), hash);

        stringstream ss;
        for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i)
            ss << hex << setw(2) << setfill('0') << static_cast<int>(hash[i]);

        return ss.str();
    }

    static bool verifyPassword(const string& password, const string& hashedPassword) {
        string hashOfInput = hashPassword(password);
        return hashOfInput == hashedPassword;
    }
};

#endif // HASH_UTIL_H
