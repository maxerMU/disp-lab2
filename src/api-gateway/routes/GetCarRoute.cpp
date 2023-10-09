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
    
    if (carUid.empty())
        throw UndefinedCarUidException("get car route");

    request->copy(m_context->GetCurrentRequest());
    request->SetTarget(GET_CAR_BASE_TARGET + "/" + carUid);
}

void GetCarRoute::ProcessResponse(const IResponsePtr &responseFromClient)
{
    if (responseFromClient->GetStatus() == net::CODE_404)
    {
        m_context->GetCurrentResponse()->SetStatus(net::CODE_404);
        return;
    }

    if (responseFromClient->GetStatus() != net::CODE_200)
    {
        m_context->GetCurrentResponse()->copy(responseFromClient);
        throw ProcessingResponseException("get car route invalid code");
    }

    CarDTO car;
    car.FromJSON(responseFromClient->GetBody());

    if (m_context->GetRequestType() == ApiGatewayContext::GetRent)
        m_context->GetProcessInfo().getRentRequest.car = car;
}
