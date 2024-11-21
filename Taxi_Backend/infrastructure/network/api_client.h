#ifndef API_CLIENT_H
#define API_CLIENT_H

#include "../../lib/lib.h"

class APIClient {
public:
    virtual ~APIClient() = default;

    virtual string performRequest(const string& url) = 0;
};

#endif // API_CLIENT_H