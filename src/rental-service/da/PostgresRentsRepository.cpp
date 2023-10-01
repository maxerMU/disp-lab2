#include "PostgresRentsRepository.h"

#include <config/base_sections.h>
#include <exceptions/database_exceptions.h>
#include <logger/LoggerFactory.h>

PostgresRentsRepository::PostgresRentsRepository(const IConfigPtr &conf, const std::string &connectionSection)
{
    ReadConfig(conf, connectionSection);
    Connect();
    AddPrepareStatements();
}

RentsDTO PostgresRentsRepository::GetRents(const std::string &username)
{
    pqxx::result rows;
    try
    {
        pqxx::work w(*m_connection);
        rows = w.exec_prepared(m_requestsNames[READ_ALL], username);
        w.commit();
    }
    catch (std::exception &ex)
    {
        throw DatabaseExecutionException(ex.what());
    }

    RentsDTO rents;
    rents.reserve(rows.size());
    for (const auto &row : rows)
    {
        RentDTO rent{
            row["id"].as<size_t>(),
            row["rental_uid"].as<std::string>(),
            row["username"].as<std::string>(),
            row["payment_uid"].as<std::string>(),
            row["car_uid"].as<std::string>(),
            row["date_from"].as<std::string>(),
            row["date_to"].as<std::string>(),
            row["status"].as<std::string>()
        };

        rents.push_back(rent);
    }

    return rents;
}

void PostgresRentsRepository::ReadConfig(const IConfigPtr &conf, const std::string &connectionSection)
{
    m_name = conf->GetStringField({connectionSection, DbNameSection});
    m_user = conf->GetStringField({connectionSection, DbUserSection});
    m_userPassword = conf->GetStringField({connectionSection, DbUserPasswordSection});
    m_host = conf->GetStringField({connectionSection, DbHostSection});
    m_port = conf->GetUintField({connectionSection, DbPortSection});
}

void PostgresRentsRepository::Connect()
{
    std::string connectionString = "dbname = " + m_name + " user = " + m_user + " password = " + m_userPassword +
                                   " host = " + m_host + " port = " + std::to_string(m_port);

    try
    {
        m_connection = std::shared_ptr<pqxx::connection>(new pqxx::connection(connectionString.c_str()));

        if (!m_connection->is_open())
            throw DatabaseConnectException("can't connect to " + m_name);
        else
            LoggerFactory::GetLogger()->LogInfo((std::string("Connected to db ") + m_name).c_str());
    }
    catch (std::exception &ex)
    {
        throw DatabaseConnectException("can't connect to " + m_name + " " + ex.what());
    }
}

void PostgresRentsRepository::AddPrepareStatements()
{
    m_connection->prepare(m_requestsNames[READ_ALL], "SELECT * FROM rents WHERE username=$1");
}

// void PostgresRentsRepository::AddPerson(const PersonPostDTO &person)
// {
//     try
//     {
//         pqxx::work w(*m_connection);
//         w.exec_prepared(m_requestsNames[WRITE], person.name, person.age, person.address, person.work);
//         w.commit();
//     }
//     catch (...)
//     {
//         throw DatabaseExecutionException("can't execute prepared");
//     }
// }