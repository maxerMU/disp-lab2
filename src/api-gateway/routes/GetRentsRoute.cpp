#include "GetRentsRoute.h"

#include "clients.h"
#include <logger/LoggerFactory.h>

void GetRentsRoute::Init(const IRequestHandlerContextPtr &context, const std::map<std::string, size_t> clients)
{
    m_context = context;
    m_clientsIndexes = clients;
}

void GetRentsRoute::SetRequestParameters(const std::vector<std::string> &)
{
}

void GetRentsRoute::ProcessRequest(const IRequestPtr &request, size_t &clientIndex)
{
    clientIndex = m_clientsIndexes[RENTS_CLIENT];
    request->copy(m_context->GetCurrentRequest());
}

void GetRentsRoute::ProcessResponse(const IResponsePtr &responseFromClient)
{
    m_context->GetCurrentResponse()->copy(responseFromClient);
}
