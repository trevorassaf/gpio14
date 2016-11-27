#pragma once

#include <cstdint>
#include <memory>

#include "PinManager.h"

namespace gpio {

class Pin {
	public:
		Pin(
      std::shared_ptr<PinManager> pin_manager,
      uint8_t index);

    // Releases the pin from its registered function.
		~Pin();

    // Returns the index of this pin.
		uint8_t GetIndex() const;

    // Asserts this pin.
    void Set();

    // Deasserts this pin.
    void Clear();
    
	private:
		uint8_t index_;

    // This pin is bound to the lifetime of the PinManager.
    std::shared_ptr<PinManager> pin_manager_;
};

} // namespace gpio
