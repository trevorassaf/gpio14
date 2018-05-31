#pragma once

#include <cstdint>
#include <cstdlib>

namespace Utils
{

class BitUtils
{
public:
	static uint8_t SetByteWithMask(uint8_t destination, uint8_t value, uint8_t mask, size_t shift)
	{
			destination &= ~mask;
			value = value << shift;
			value &= mask;
			destination |= value;
			return destination;
	}

	static uint8_t SetBitWithMask(uint8_t destination, bool value, uint8_t mask, size_t shift)
	{
			return SetByteWithMask(
					destination,
					static_cast<uint8_t>(value),
					mask,
					shift);
	}

	static uint8_t GetBits(uint8_t reg, uint8_t mask, size_t shift)
	{
			reg &= mask;
			return reg >> shift;
	}
};

} // namespace Utils
