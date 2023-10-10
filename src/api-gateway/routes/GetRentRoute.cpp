#include "GetRentRoute.h"

#include <exceptions/server_exceptions.h>
#include <logger/LoggerFactory.h>

#include "clients.h"

void GetRentRoute::Init(const IRequestHandlerContextPtr &context, const std::map<std::string, size_t> clients)
{
    m_context = std::dynamic_pointer_cast<ApiGatewayContext>(context);
    if (!m_context)
        throw ContextPtrCastException("get rent route");

    m_clientsIndexes = clients;
}

void GetRentRoute::SetRequestParameters(const std::vector<std::string> &)
{
}

void GetRentRoute::ProcessRequest(const IRequestPtr &request, size_t &clientIndex)
{
    clientIndex = m_clientsIndexes[RENTS_CLIENT];

    const std::string rentUid = m_context->GetProcessInfo().getRentRequest.rentUid;
    request->copy(m_context->GetCurrentRequest());
    request->SetTarget(GET_RENT_BASE_TARGET + "/" + rentUid);
}

IClientServerRoute::ResponceType GetRentRoute::ProcessResponse(const IResponsePtr &responseFromClient)
{
    if (responseFromClient->GetStatus() == net::CODE_404)
    {
        m_context->GetCurrentResponse()->SetStatus(net::CODE_404);
        return IClientServerRoute::END_ROUTE;
    }

    if (responseFromClient->GetStatus() != net::CODE_200)
    {
        m_context->GetCurrentResponse()->copy(responseFromClient);
        throw ProcessingResponseException("get rent route invalid code");
    }

    m_context->GetProcessInfo().getRentRequest.rent.FromJSON(responseFromClient->GetBody());
    return IClientServerRoute::END_ROUTE;
}
