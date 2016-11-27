#include "Pin.h"

#include <utility>

namespace gpio {

Pin::Pin(
    std::shared_ptr<PinManager> pin_manager,
    uint8_t index)
  : pin_manager_(std::move(pin_manager)),
    index_(index) {}

Pin::~Pin() {
  pin_manager_->ReleasePin(index_);
}

uint8_t Pin::GetIndex() const {
	return index_;
}

void Pin::Set() {
  pin_manager_->SetPin(index_);
}

void Pin::Clear() {
  pin_manager_->ClearPin(index_);
}

} // namespace gpio
