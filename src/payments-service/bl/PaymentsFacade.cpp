#include "PaymentsFacade.h"

#include <exceptions/database_exceptions.h>
#include <exceptions/logic_exceptions.h>

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

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

PaymentDTO PaymentsFacade::AddPayment(const PostPaymentDTO &payment) const
{
    if (!m_repository)
        throw NotInitializedException("repository doesn't initilized");
    
    boost::uuids::random_generator gen;
    boost::uuids::uuid uuid = gen();

    std::string uuidStr = boost::uuids::to_string(uuid);
    m_repository->AddPayment(uuidStr, payment.price);

    return {uuidStr, "PAID", payment.price};
}
