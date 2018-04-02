#include "I2c/Devices/Tsl2561LuxMeter/Tsl2561QuantizedLuxCalculator.h"

#include <cstdlib>
#include <cstdint>

namespace
{
constexpr size_t LUX_SCALE = 14; // scale by 2^14
constexpr size_t RATIO_SCALE = 9; // scale by 2^9

constexpr size_t CHSCALE = 10; // scale values by 2^10
constexpr size_t CHSCALE_TINT0 = 0x7517; // scale by 322/11 * 2^CHSCALE
constexpr size_t CHSCALE_TINT1 = 0x0FE7; // scale by 322/81 * 2^CHSCALE

constexpr size_t K1T = 0x0040; // 0.125 * 2^RATIO_SCALE
constexpr size_t B1T = 0x01f2; // 0.0304 * 2^LUX_SCALE
constexpr size_t M1T = 0x01be; // 0.0272 * 2^LUX_SCALE
constexpr size_t K2T = 0x0080; // 0.250 * 2^RATIO_SCALE

constexpr size_t B2T = 0x0214; // 0.0325 * 2^LUX_SCALE
constexpr size_t M2T = 0x02d1; // 0.0440 * 2^LUX_SCALE
constexpr size_t K3T = 0x00c0; // 0.375 * 2^RATIO_SCALE
constexpr size_t B3T = 0x023f; // 0.0351 * 2^LUX_SCALE
constexpr size_t M3T = 0x037b; // 0.0544 * 2^LUX_SCALE
constexpr size_t K4T = 0x0100; // 0.50 * 2^RATIO_SCALE
constexpr size_t B4T = 0x0270; // 0.0381 * 2^LUX_SCALE
constexpr size_t M4T = 0x03fe; // 0.0624 * 2^LUX_SCALE
constexpr size_t K5T = 0x0138; // 0.61 * 2^RATIO_SCALE
constexpr size_t B5T = 0x016f; // 0.0224 * 2^LUX_SCALE
constexpr size_t M5T = 0x01fc; // 0.0310 * 2^LUX_SCALE
constexpr size_t K6T = 0x019a; // 0.80 * 2^RATIO_SCALE
constexpr size_t B6T = 0x00d2; // 0.0128 * 2^LUX_SCALE
constexpr size_t M6T = 0x00fb; // 0.0153 * 2^LUX_SCALE
constexpr size_t K7T = 0x029a; // 1.3 * 2^RATIO_SCALE
constexpr size_t B7T = 0x0018; // 0.00146 * 2^LUX_SCALE
constexpr size_t M7T = 0x0012; // 0.00112 * 2^LUX_SCALE
constexpr size_t K8T = 0x029a; // 1.3 * 2^RATIO_SCALE
constexpr size_t B8T = 0x0000; // 0.000 * 2^LUX_SCALE
constexpr size_t M8T = 0x0000; // 0.000 * 2^LUX_SCALE

constexpr size_t K1C = 0x0043; // 0.130 * 2^RATIO_SCALE
constexpr size_t B1C = 0x0204; // 0.0315 * 2^LUX_SCALE
constexpr size_t M1C = 0x01ad; // 0.0262 * 2^LUX_SCALE
constexpr size_t K2C = 0x0085; // 0.260 * 2^RATIO_SCALE
constexpr size_t B2C = 0x0228; // 0.0337 * 2^LUX_SCALE
constexpr size_t M2C = 0x02c1; // 0.0430 * 2^LUX_SCALE
constexpr size_t K3C = 0x00c8; // 0.390 * 2^RATIO_SCALE
constexpr size_t B3C = 0x0253; // 0.0363 * 2^LUX_SCALE
constexpr size_t M3C = 0x0363; // 0.0529 * 2^LUX_SCALE

constexpr size_t K4C = 0x010a; // 0.520 * 2^RATIO_SCALE
constexpr size_t B4C = 0x0282; // 0.0392 * 2^LUX_SCALE
constexpr size_t M4C = 0x03df; // 0.0605 * 2^LUX_SCALE
constexpr size_t K5C = 0x014d; // 0.65 * 2^RATIO_SCALE
constexpr size_t B5C = 0x0177; // 0.0229 * 2^LUX_SCALE
constexpr size_t M5C = 0x01dd; // 0.0291 * 2^LUX_SCALE
constexpr size_t K6C = 0x019a; // 0.80 * 2^RATIO_SCALE
constexpr size_t B6C = 0x0101; // 0.0157 * 2^LUX_SCALE
constexpr size_t M6C = 0x0127; // 0.0180 * 2^LUX_SCALE
constexpr size_t K7C = 0x029a; // 1.3 * 2^RATIO_SCALE
constexpr size_t B7C = 0x0037; // 0.00338 * 2^LUX_SCALE
constexpr size_t M7C = 0x002b; // 0.00260 * 2^LUX_SCALE
constexpr size_t K8C = 0x029a; // 1.3 * 2^RATIO_SCALE
constexpr size_t B8C = 0x0000; // 0.000 * 2^LUX_SCALE
constexpr size_t M8C = 0x0000; // 0.000 * 2^LUX_SCALE

void setNonCsPackageParams(uint64_t channelRatio, uint32_t *outB, uint32_t *outM)
{
		if (channelRatio >= 0 && channelRatio <= K1T)
		{
				*outB = B1T;
				*outM = M1T;
		}
		else if (channelRatio <= K2T)
		{
				*outB = B2T;
				*outM = M2T;
		}
		else if (channelRatio <= K3T)
		{
				*outB = B3T;
				*outM = M3T;
		}
		else if (channelRatio <= K4T)
		{
				*outB = B4T;
				*outM = M4T;
		}
		else if (channelRatio <= K5T)
		{
				*outB = B5T;
				*outM = M5T;
		}
		else if (channelRatio <= K6T)
		{
				*outB = B6T;
				*outM = M6T;
		}
		else if (channelRatio <= K7T)
		{
				*outB = B7T;
				*outM = M7T;
		}
		else if (channelRatio > K8T)
		{
				*outB = B8T;
				*outM = M8T;
		}
}

void setCsPackageParams(uint64_t channelRatio, uint32_t *outB, uint32_t *outM)
{
		if (channelRatio >= 0 && channelRatio <= K1C)
		{
				*outB = B1C;
				*outM = M1C;
		}
		else if (channelRatio <= K2C)
		{
				*outB = B2C;
				*outM = M2C;
		}
		else if (channelRatio <= K3C)
		{
				*outB = B3C;
				*outM = M3C;
		}
		else if (channelRatio <= K4C)
		{
				*outB = B4C;
				*outM = M4C;
		}
		else if (channelRatio <= K5C)
		{
				*outB = B5C;
				*outM = M5C;
		}
		else if (channelRatio <= K6C)
		{
				*outB = B6C;
				*outM = M6C;
		}
		else if (channelRatio <= K7C)
		{
				*outB = B7C;
				*outM = M7C;
		}
		else if (channelRatio > K8C)
		{
				*outB = B8C;
				*outM = M8C;
		}
}
} // namespace

namespace I2c
{
Tsl2561QuantizedLuxCalculator::Tsl2561QuantizedLuxCalculator() : stuff{} {}

Tsl2561LuxValues Tsl2561QuantizedLuxCalculator::ComputeQuantizedLux(
	 uint32_t iGain,
	 uint32_t tInt,
	 uint16_t ch0,
	 uint16_t ch1,
	 int iType) const
{
    uint64_t chScale;
    uint64_t channel0;
    uint64_t channel1;

    switch (tInt)
    {
        case 0:  // 13.7 ms
          chScale = CHSCALE_TINT0;
          break;
        case 1:  // 101 ms
          chScale = CHSCALE_TINT1;
          break;
        default: // no scaling
          chScale = (1 << CHSCALE);
          break;
    }

    // Scale if gain is not 16x
    if (!iGain)
    {
				// Scale from 1x to 16x
        chScale = chScale << 4;
    }

		// Scale the channel values
		channel0 = (ch0 * chScale) >> CHSCALE;
		channel1 = (ch1 * chScale) >> CHSCALE;

		// Find the ratio of the channel values (ch1/ch0). Protect against divide by zero.
		uint64_t channelRatio = 0;
		if (ch0 != 0)
		{
				channelRatio = (ch1 << (RATIO_SCALE + 1)) / ch0;
		}

		// Round ratio
		channelRatio = (channelRatio + 1) >> 1;

		uint32_t b, m;

		if (iType)
		{
				setNonCsPackageParams(channelRatio, &b, &m);
		}
		else
		{
				setCsPackageParams(channelRatio, &b, &m);
		}

		int32_t temp;
		temp = ch0 * b - ch1 * m;

		if (temp < 0)
		{
				temp = 0;
		}

		temp += (1 << (LUX_SCALE - 1));

		uint32_t luxValue = temp >> LUX_SCALE;
		return Tsl2561LuxValues{ch0, luxValue};
}
} // namespace I2c
