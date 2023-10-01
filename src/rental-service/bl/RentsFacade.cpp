#include "RentsFacade.h"

#include <exceptions/database_exceptions.h>
#include <exceptions/logic_exceptions.h>

std::shared_ptr<RentsFacade> RentsFacade::Instance()
{
    static std::shared_ptr<RentsFacade> instance(new RentsFacade());
    return instance;
}

void RentsFacade::Init(const IRentsRepositoryPtr &repository)
{
    m_repository = repository;
}

RentsDTO RentsFacade::GetRents(std::string username) const
{
    if (!m_repository)
        throw NotInitializedException("repository doesn't initilized");

    return m_repository->GetRents(username);
}