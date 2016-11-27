#include "PinFactory.h"

#include <utility>

namespace gpio {

PinFactory::PinFactory(std::unique_ptr<PinManager> pin_manager)
    : pin_manager_(std::move(pin_manager)) {}

} // namespace gpio
