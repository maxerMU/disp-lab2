#include "RentsGateway.h"

#include "bl/RentsFacade.h"
#include <exceptions/logic_exceptions.h>
#include <logger/LoggerFactory.h>
#include <router/router.h>

void Health(const IResponsePtr &resp, const IRequestPtr &)
{
    resp->SetStatus(net::CODE_200);
}

void GetRents(const IResponsePtr &resp, const IRequestPtr &request)
{
    headers_t headers = request->GetHeaders();
    auto it = headers.find("X-User-Name");
    if (it == headers.end())
    {
        LoggerFactory::GetLogger()->LogError("header X-User-Name not found");
        resp->SetStatus(net::CODE_400);
        return;
    }

    std::string username = it->first;
    RentsDTO rents = RentsFacade::Instance()->GetRents(username);
    resp->SetBody(ToJSON(rents));
    resp->SetStatus(net::CODE_200);
}

void SetupRouter()
{
    RequestsRouter::Instanse()->AddStaticEndpoint({"/manage/health", net::GET}, Health);
    RequestsRouter::Instanse()->AddStaticEndpoint({"/api/v1/rental", net::GET}, GetRents);
}
