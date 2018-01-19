#pragma once

#include <cstdint>

namespace I2c
{
class Tsl2561HalfWord
{
public:
	virtual uint16_t HalfWord() const = 0;
};
} // namespace I2c
