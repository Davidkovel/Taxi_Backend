#ifndef CALCULATE_DISTANCE_H
#define CALCULATE_DISTANCE_H

#include "../infrastructure/network/api_client_impl.h"
#include "../infrastructure/network/serializer.h"

class CalculateDistance {
public:
    ResponseData execute(const string& origin, const string& destination, const string& apiKey) {
        try {

            APIClientImpl apiClient;
            string url = Serializer::serializeRequest(origin, destination, apiKey);

            string response = apiClient.performRequest(url);

            ResponseData result = Serializer::deserializeResponse(response);

            cout << "Distance: " << result.distance << "\n";
            cout << "Duration: " << result.duration << "\n";

            return result;
        }
        catch (const exception& ex) {
            throw exceptions::ProcessException("Error during distance calculation " + string(ex.what()));
        }

    }
};

#endif // CALCULATE_DISTANCE_H
