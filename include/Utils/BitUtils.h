#pragma once

#include <cstdint>

namespace Utils
{

class BitUtils
{
public:
	static uint8_t SetByteWithMask(uint8_t destination, uint8_t value, uint8_t mask, uint8_t shift)
	{
			destination &= ~mask;
			value = value << shift;
			value &= mask;
			destination |= value;
			return destination;
	}

	static uint8_t SetBitWithMask(uint8_t destination, bool value, uint8_t mask, uint8_t shift)
	{
			uint8_t byteValue = static_cast<uint8_t>(value);
			return SetByteWithMask(destination, byteValue, mask, shift);
	}
};

} // namespace Utils
