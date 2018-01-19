#pragma once

#include <cstdint>

namespace Utils
{

class BitUtils
{
public:
	static uint8_t SetByteWithMask(uint8_t destination, uint8_t value, uint8_t mask)
	{
			destination &= ~mask;
			value &= mask;
			destination |= value;
			return destination;
	}

	static uint8_t SetBitWithMask(uint8_t destination, bool value, uint8_t mask)
	{
			uint8_t byteValue = (value) ? mask : 0;
			return SetByteWithMask(destination, byteValue, mask);
	}
};

} // namespace Utils
