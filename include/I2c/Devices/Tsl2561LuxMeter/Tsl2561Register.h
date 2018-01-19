#pragma once

#include <cstdint>

namespace I2c
{

class Tsl2561Register
{
public:
	virtual uint8_t Bits() const = 0;
};

} // namespace I2c
