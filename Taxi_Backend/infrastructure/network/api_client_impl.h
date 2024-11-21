#ifndef API_CLIENT_IMPL_H
#define API_CLIENT_IMPL_H

#include "api_client.h"

class APIClientImpl : public APIClient {
public:
    APIClientImpl() = default;
    
    string performRequest(const string& url) override {
        CURL* curl;
        CURLcode res;
        string response;

        curl = curl_easy_init();
        if (curl) {
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

            res = curl_easy_perform(curl);
            if (res != CURLE_OK) {
                throw runtime_error("CURL request failed: " + string(curl_easy_strerror(res)));
            }

            curl_easy_cleanup(curl);
        }
        return response;
    }

private:
    string apiKey = apiKey;
    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, string* output) {
        size_t totalSize = size * nmemb;
        output->append((char*)contents, totalSize);
        return totalSize;
    }
};

#endif // API_CLIENT_IMPL_H
