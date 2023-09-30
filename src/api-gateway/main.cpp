#include <config/config_creators.h>
#include <logger/LoggerFactory.h>
#include <network/net.h>
#include <router/router.h>

#include <memory>

#include "ApiGatewayHandler.h"
#include "routes/GetCarsRoute.h"

void SetupRouter()
{
    std::vector<IClientServerRouteCreatorPtr> getCarsRoute{
        std::make_shared<ClientServerRouteCreator<GetCarsRoute>>()
    };
    std::regex getCarsTarget("/api/v1/cars\\?page=([0-9\\-]+)&size=([0-9\\-]+)&showAll=(true|false)");
    RequestsRouter::Instanse()->AddDynamicEndpoint({getCarsTarget, net::GET}, getCarsRoute);
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        return 1;
    }

    SetupRouter();

    asio::io_context ioc;

    std::shared_ptr<IConfig> config = CreateYAMLConfig(std::string(argv[1]));
    LoggerFactory::InitLogger(config);

    auto handlerCreator = std::make_shared<ClientServerReqHandlerCreator<ApiGatewayHandler>>(config);
    auto sessionCreator = CreateClientServerSessionCreator(handlerCreator);
    auto connection = CreateClientServerConnection(ioc, sessionCreator, config);

    connection->Run();

    return 0;
}
