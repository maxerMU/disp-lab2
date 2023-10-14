#include "UpdateCarAvailabilityRoute.h"

#include <exceptions/server_exceptions.h>
#include <exceptions/logic_exceptions.h>
#include <logger/LoggerFactory.h>

#include "clients.h"
#include "dto/CarAvailabilityDTO.h"

void UpdateCarAvailabilityRoute::Init(const IRequestHandlerContextPtr &context, const std::map<std::string, size_t> clients)
{
    m_context = std::dynamic_pointer_cast<ApiGatewayContext>(context);
    if (!m_context)
        throw ContextPtrCastException("update car route");

    m_clientsIndexes = clients;
}

void UpdateCarAvailabilityRoute::SetRequestParameters(const std::vector<std::string> &)
{
}

void UpdateCarAvailabilityRoute::ProcessRequest(const IRequestPtr &request, size_t &clientIndex)
{
    clientIndex = m_clientsIndexes[CARS_CLIENT];

    std::string carUid;
    bool availability;
    if (m_context->GetRequestType() == ApiGatewayContext::PostRent)
    {
        carUid = m_context->GetProcessInfo().postRentRequest.car.carUid;
        availability = false;
    }
    else if (m_context->GetRequestType() == ApiGatewayContext::FinishRent)
    {
        carUid = m_context->GetProcessInfo().finishRentRequest.rent.carUid;
        availability = true;
    }
    else if (m_context->GetRequestType() == ApiGatewayContext::CancelRent)
    {
        carUid = m_context->GetProcessInfo().cancelRentRequest.rent.carUid;
        availability = true;
    }
    
    if (carUid.empty())
        throw UndefinedCarUidException("get car route");

    CarAvailabilityDTO car{carUid, availability};

    request->SetMethod(net::PATCH);
    request->SetBody(car.ToJSON());
    request->SetTarget(GET_CAR_BASE_TARGET);
}

IClientServerRoute::ResponceType UpdateCarAvailabilityRoute::ProcessResponse(const IResponsePtr &responseFromClient)
{
    if (responseFromClient->GetStatus() == net::CODE_404)
    {
        m_context->GetCurrentResponse()->SetStatus(net::CODE_404);
        return IClientServerRoute::END_ROUTE;
    }

    if (responseFromClient->GetStatus() != net::CODE_200)
    {
        m_context->GetCurrentResponse()->copy(responseFromClient);
        throw ProcessingResponseException("get car route invalid code");
    }

    return IClientServerRoute::END_ROUTE;
}
