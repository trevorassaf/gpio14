#pragma once

#include <cstdint>

namespace I2c
{
class Tsl2561HalfWord
{
public:
	virtual uint16_t GetHalfWord() const = 0;
};
} // namespace I2c
