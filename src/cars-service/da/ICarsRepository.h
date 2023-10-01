#pragma once

#include <memory>

#include <dto/CarDTO.h>

class ICarsRepository
{
public:
    virtual ~ICarsRepository() = default;

    virtual CarsDTO GetAllCars() = 0;
    virtual CarsDTO GetAvailableCars() = 0;
};

using ICarsRepositoryPtr = std::shared_ptr<ICarsRepository>;