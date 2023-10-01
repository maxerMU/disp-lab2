#pragma once

#include "IRentsRepository.h"
#include <config/IConfig.h>

const std::string RentsDBSection = "DB_RentS";

IRentsRepositoryPtr CreateRentsRepository(const IConfigPtr &conf, const std::string &connectionSection);