#include "CarsGateway.h"

#include <exceptions/logic_exceptions.h>
#include <router/router.h>
#include <logger/LoggerFactory.h>
#include "bl/CarsFacade.h"

void Check(const IResponsePtr &resp, const IRequestPtr &, const std::vector<std::string> &params)
{
    if (params.size() != 1)
        return resp->SetStatus(net::CODE_503);

    resp->SetBody(params[0]);
    resp->SetStatus(net::CODE_200);
}

void Health(const IResponsePtr &resp, const IRequestPtr &)
{
    resp->SetStatus(net::CODE_200);
}

void GetCars(const IResponsePtr &resp, const IRequestPtr &, const std::vector<std::string>& params)
{
    if (params.size() != 3)
    {
        LoggerFactory::GetLogger()->LogError("get cars incorrect params number");
        resp->SetStatus(net::CODE_400);
    }

    size_t page = std::stoull(params[0]);
    size_t pageSize = std::stoull(params[1]);
    bool showAll = (strcasecmp(params[2].c_str(), "true") == 0);

    CarsDTO cars = CarsFacade::Instance()->GetCars(page, pageSize, showAll);

    resp->SetBody(ToJSON(cars, page, pageSize));
    resp->SetStatus(net::CODE_200);
}


void SetupRouter()
{
    RequestsRouter::Instanse()->AddStaticEndpoint({"/manage/health", net::GET}, Health);

    std::regex getCarsTarget("/api/v1/cars\\?page=([0-9\\-]+)&size=([0-9\\-]+)&showAll=(true|false)");
    RequestsRouter::Instanse()->AddDynamicEndpoint({getCarsTarget, net::GET}, GetCars);
}
