// IDriverRepository.h
#ifndef IDRIVER_REPOSITORY_H
#define IDRIVER_REPOSITORY_H

#include "../../domain/domain.h"

class IDriverRepository {
public:
    virtual vector<int> getAvailableDriverIds() = 0;
    virtual void updateDriverBalance(int driverId, double newBalance) = 0;
    virtual ~IDriverRepository() = default;
};

#endif // IUSER_REPOSITORY_H
