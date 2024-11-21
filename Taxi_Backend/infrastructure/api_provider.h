#ifndef API_PROVIDER_H
#define API_PROVIDER_H

#include "../infrastructure/network/api_client_impl.h"
#include "../infrastructure/network/serializer.h"

class ApiProvider {
private:
	APIClientImpl api_client;
public:
	APIClientImpl* setApiDistance()
	{
		return &api_client;
	}

};

#endif // API_PROVIDER_H