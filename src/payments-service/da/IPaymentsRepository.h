#pragma once

#include <memory>

#include <dto/PaymentDTO.h>

class IPaymentsRepository
{
public:
    virtual ~IPaymentsRepository() = default;

    virtual PaymentDTO GetPayment(const std::string &uid) = 0;
};

using IPaymentsRepositoryPtr = std::shared_ptr<IPaymentsRepository>;