#include "GetCarsRoute.h"

#include "clients.h"
#include <logger/LoggerFactory.h>

void GetCarsRoute::Init(const IRequestHandlerContextPtr &context, const std::map<std::string, size_t> clients)
{
    m_context = context;
    m_clientsIndexes = clients;
}

void GetCarsRoute::SetRequestParameters(const std::vector<std::string> &params)
{
    for (const auto& param : params)
        LoggerFactory::GetLogger()->LogInfo(param.c_str());
}

void GetCarsRoute::ProcessRequest(const IRequestPtr &request, size_t &clientIndex)
{
    clientIndex = m_clientsIndexes[DUMMY_CLIENT];
    request->SetTarget("/info");
    request->SetMethod(net::GET);
}

void GetCarsRoute::ProcessResponse(const IResponsePtr &responseFromClient)
{
    m_context->GetCurrentResponse()->copy(responseFromClient);
}
