#include "Pin.h"

namespace gpio {

Pin::Pin(uint8_t index) : index_(index) {}

Pin::~Pin() {}

uint8_t Pin::GetIndex() const {
	return index_;
}

} // namespace gpio
