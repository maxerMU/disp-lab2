#pragma once

#include <map>
#include <pqxx/pqxx>

#include "ICarsRepository.h"
#include <config/IConfig.h>

class PostgresCarsRepository : public ICarsRepository
{
public:
    PostgresCarsRepository(const IConfigPtr &conf, const std::string &connectionSection);

    virtual CarsDTO GetAllCars() override;
    virtual CarsDTO GetAvailableCars() override;

private:
    void ReadConfig(const IConfigPtr &conf, const std::string &connectionSection);

    void Connect();
    void AddPrepareStatements();

    std::shared_ptr<pqxx::connection> m_connection;

    std::string m_name;
    std::string m_user;
    std::string m_userPassword;
    std::string m_host;
    size_t m_port;

    enum PreparedRequests
    {
        READ_AVAILABLE,
        READ_ALL,
    };

    std::map<PreparedRequests, std::string> m_requestsNames = {
        {READ_AVAILABLE, "get_available_cars"},
        {READ_ALL, "get_all_persons"}
    };
};