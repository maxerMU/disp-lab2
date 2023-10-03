#include "PaymentsFacade.h"

#include <exceptions/database_exceptions.h>
#include <exceptions/logic_exceptions.h>

std::shared_ptr<PaymentsFacade> PaymentsFacade::Instance()
{
    static std::shared_ptr<PaymentsFacade> instance(new PaymentsFacade());
    return instance;
}

void PaymentsFacade::Init(const IPaymentsRepositoryPtr &repository)
{
    m_repository = repository;
}

PaymentDTO PaymentsFacade::GetPayment(const std::string &uid) const
{
    if (!m_repository)
        throw NotInitializedException("repository doesn't initilized");
    
    try
    {
        return m_repository->GetPayment(uid);
    }
    catch(const DatabaseNotFoundException& e)
    {
        throw PaymentNotFoundException(e.what());
    }
}
