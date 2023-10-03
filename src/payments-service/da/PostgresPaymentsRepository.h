#pragma once

#include <map>
#include <pqxx/pqxx>

#include "IPaymentsRepository.h"
#include <config/IConfig.h>

class PostgresPaymentsRepository : public IPaymentsRepository
{
public:
    PostgresPaymentsRepository(const IConfigPtr &conf, const std::string &connectionSection);

    virtual PaymentDTO GetPayment(const std::string &uid) override;

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
        READ
    };

    std::map<PreparedRequests, std::string> m_requestsNames = {
        {READ, "get_payment"}
    };
};