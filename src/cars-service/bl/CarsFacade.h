#pragma once

#include <memory>

#include <da/ICarsRepository.h>
#include <dto/CarDTO.h>

class CarsFacade
{
public:
    static std::shared_ptr<CarsFacade> Instance();
    void Init(const ICarsRepositoryPtr &repository);

    CarsDTO GetCars(size_t page, size_t pageSize, bool showAll) const;

private:
    CarsFacade() = default;

    ICarsRepositoryPtr m_repository;
};