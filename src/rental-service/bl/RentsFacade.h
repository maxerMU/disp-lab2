#pragma once

#include <memory>

#include <da/IRentsRepository.h>
#include <dto/RentDTO.h>

class RentsFacade
{
public:
    static std::shared_ptr<RentsFacade> Instance();
    void Init(const IRentsRepositoryPtr &repository);

    RentsDTO GetRents(const std::string& username) const;
    RentDTO GetRent(const std::string& username, const std::string& rentalUid) const;

private:
    RentsFacade() = default;

    IRentsRepositoryPtr m_repository;
};