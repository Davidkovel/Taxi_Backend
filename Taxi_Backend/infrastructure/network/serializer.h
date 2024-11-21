#ifndef SERIALIZER_H
#define SERIALIZER_H

#include "../../lib/lib.h"

struct ResponseData {
    string distance;
    string duration;
};

class Serializer {
public:
    static string serializeRequest(const string& origin, const string& destination, const string& key) {
        string url = "https://api.distancematrix.ai/maps/api/distancematrix/json";
        url += "?origins=" + origin + "&destinations=" + destination + "&key=" + key;
        return url;
    }

    static ResponseData deserializeResponse(const string& jsonResponse) {
        auto data = json::parse(jsonResponse);
        ResponseData response_data;

        if (data.contains("rows") && !data["rows"].empty()) {
            auto elements = data["rows"][0]["elements"][0];
            string distance = elements["distance"]["text"];
            string duration = elements["duration"]["text"];

            response_data.distance = distance;
            response_data.duration = duration;

            return response_data;
        }
        throw runtime_error("Invalid JSON structure");
    }
};

#endif // SERIALIZER_H
