#pragma once

#include "base_exception.h"

PROJECT_EXCEPTION(LogicException, BaseException, "(Logic error)")
PROJECT_EXCEPTION(NotInitializedException, LogicException, "(Not initialized member)")
PROJECT_EXCEPTION(NotValidPageException, LogicException, "(Not valid page)")
PROJECT_EXCEPTION(InvalidAuthDataException, LogicException, "(Invalid auth data)")
PROJECT_EXCEPTION(PaymentNotFoundException, LogicException, "(Payment not found)")
