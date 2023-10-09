#pragma once

#include <memory>

#include <dto/RentDTO.h>

class IRentsRepository
{
public:
    virtual ~IRentsRepository() = default;

    virtual RentsDTO GetRents(const std::string& username) = 0;
    virtual RentDTO GetRent(const std::string& username, const std::string& rentalUid) = 0;
};

using IRentsRepositoryPtr = std::shared_ptr<IRentsRepository>;