#pragma once

#include <memory>

#include <dto/PaymentDTO.h>
#include <dto/PostPaymentDTO.h>

class IPaymentsRepository
{
public:
    virtual ~IPaymentsRepository() = default;

    virtual PaymentDTO GetPayment(const std::string &uid) = 0;
    virtual void AddPayment(const std::string &paymentUid, size_t price) = 0;
};

using IPaymentsRepositoryPtr = std::shared_ptr<IPaymentsRepository>;