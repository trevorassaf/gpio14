#pragma once

#include <bitset>
#include <cstdint>
#include <cstdlib>
#include <string>

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

  static uint32_t Rotate(uint32_t bytes)
  {
      uint32_t outBytes = 0;

      for (size_t i = 0; i < sizeof(bytes); ++i)
      {
          outBytes <<= 8;
          outBytes |= bytes & 0xFF;
          bytes >>= 8;
      }

      return outBytes;
  }

  static uint32_t RotateBits(uint32_t bytes, size_t numBitsToRotate)
  {
      uint32_t outBytes = 0;

      for (size_t i = 0; i < numBitsToRotate; ++i)
      {
          outBytes |= bytes % 2;
          outBytes <<= 1;
          bytes >>= 1;
      }

      return outBytes;
  }

  static std::string ToBitString(uint32_t bytes)
  {
      std::bitset<32> bits{bytes};
      return bits.to_string();
  }
};

} // namespace Utils
