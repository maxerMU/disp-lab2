#include "GetCarRoute.h"

#include <exceptions/server_exceptions.h>
#include <exceptions/logic_exceptions.h>
#include <logger/LoggerFactory.h>

#include "clients.h"

void GetCarRoute::Init(const IRequestHandlerContextPtr &context, const std::map<std::string, size_t> clients)
{
    m_context = std::dynamic_pointer_cast<ApiGatewayContext>(context);
    if (!m_context)
        throw ContextPtrCastException("get car route");

    m_clientsIndexes = clients;
}

void GetCarRoute::SetRequestParameters(const std::vector<std::string> &)
{
}

void GetCarRoute::ProcessRequest(const IRequestPtr &request, size_t &clientIndex)
{
    clientIndex = m_clientsIndexes[CARS_CLIENT];

    std::string carUid;
    if (m_context->GetRequestType() == ApiGatewayContext::GetRent)
        carUid = m_context->GetProcessInfo().getRentRequest.rent.carUid;
    else if (m_context->GetRequestType() == ApiGatewayContext::GetRents)
        carUid = m_context->GetProcessInfo().getRentsRequest.rents[m_iteration].carUid;
    
    if (carUid.empty())
        throw UndefinedCarUidException("get car route");

    request->copy(m_context->GetCurrentRequest());
    request->SetTarget(GET_CAR_BASE_TARGET + "/" + carUid);
}

IClientServerRoute::ResponceType GetCarRoute::ProcessResponse(const IResponsePtr &responseFromClient)
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

    CarDTO car;
    car.FromJSON(responseFromClient->GetBody());

    if (m_context->GetRequestType() == ApiGatewayContext::GetRent)
    {
        m_context->GetProcessInfo().getRentRequest.car = car;
        return IClientServerRoute::END_ROUTE;
    }
    else if (m_context->GetRequestType() == ApiGatewayContext::GetRents)
    {
        m_context->GetProcessInfo().getRentsRequest.cars.push_back(car);
        m_iteration++;
        if (m_iteration < m_context->GetProcessInfo().getRentsRequest.rents.size())
            return IClientServerRoute::REPEAT_ROUTE;
    }

    return IClientServerRoute::END_ROUTE;
}
