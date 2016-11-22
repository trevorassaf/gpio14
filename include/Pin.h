#pragma once

#include <cstdint>
#include <memory>

namespace gpio {

class Pin {
	public:
		Pin(uint8_t index);
		~Pin();

		uint8_t GetIndex() const;
	private:
		uint8_t index_;
};

} // namespace gpio
