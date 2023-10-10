#pragma once

#include <router/IRequestHandlerContext.h>

#include "dto/RentDTO.h"
#include "dto/CarDTO.h"
#include "dto/PaymentDTO.h"

class ApiGatewayContext 
    : public IRequestHandlerContext
{
public:
    ApiGatewayContext();
    virtual ~ApiGatewayContext() = default;
    virtual IRequestPtr GetCurrentRequest() override;
    virtual IResponsePtr GetCurrentResponse() override;

    enum RequestType
    {
        Undefined,
        GetRent,
        GetRents
    };
    RequestType GetRequestType() const;
    void SetRequestType(const RequestType& reqType);

    // TODO boost variant
    struct RequestProcessInfo
    {
        struct GetRentRequest
        {
            std::string rentUid;
            RentDTO rent;
            CarDTO car;
            PaymentDTO payment;
        } getRentRequest;

        struct GetRentsRequest
        {
            RentsDTO rents;
            CarsDTO cars;
            PaymentsDTO payments;
        } getRentsRequest;
        
    };
    RequestProcessInfo& GetProcessInfo();
    
private:
    IRequestHandlerContextPtr m_context;

    RequestType m_requestType = Undefined;
    RequestProcessInfo m_requestProcessInfo;
};

using ApiGatewayContextPtr = std::shared_ptr<ApiGatewayContext>;