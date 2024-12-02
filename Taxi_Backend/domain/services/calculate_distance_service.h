#ifndef DISTANCE_CALCULATION_SERVICE_H
#define DISTANCE_CALCULATION_SERVICE_H

#include "../../infrastructure/network/api_client_impl.h"
#include "../../infrastructure/network/serializer.h"

class DistanceCalculationService {
public:
    ResponseData calculateDistance(const string& origin, const string& destination, const string& apiKey) {
        try {
            APIClientImpl apiClient;
            string url = Serializer::serializeRequest(origin, destination, apiKey);

            string response = apiClient.performRequest(url);

            ResponseData result = Serializer::deserializeResponse(response);

            if (response.empty()) {
                throw exceptions::ProcessException("Received empty response from the API.");
            }

            return result;
        }
        catch (const exception& ex) {
            cout << "No such city" << endl;
            throw;
           // throw exceptions::ProcessException("Error during distance calculation: " + string(ex.what()));
        }
    }
};

#endif // DISTANCE_CALCULATION_SERVICE_H
