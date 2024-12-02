#ifndef DISTANCE_CALCULATION_USE_CASE_H
#define DISTANCE_CALCULATION_USE_CASE_H

#include "../services/calculate_distance_service.h"

class DistanceCalculationUseCase {
private:
    DistanceCalculationService* distanceCalculationService;

public:
    explicit DistanceCalculationUseCase(DistanceCalculationService* service) : distanceCalculationService(service) {}

    ResponseData execute(const string& origin, const string& destination, const string& apiKey) {
        return distanceCalculationService->calculateDistance(origin, destination, apiKey);
    }
};

#endif // DISTANCE_CALCULATION_USE_CASE_H
