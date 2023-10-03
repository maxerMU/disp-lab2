#pragma once

#include <memory>

#include <da/IPaymentsRepository.h>
#include <dto/PaymentDTO.h>

class PaymentsFacade
{
public:
    static std::shared_ptr<PaymentsFacade> Instance();
    void Init(const IPaymentsRepositoryPtr &repository);

    PaymentDTO GetPayment(const std::string& uid) const;

private:
    PaymentsFacade() = default;

    IPaymentsRepositoryPtr m_repository;
};