#pragma once

#include <array>
#include <cstdint>
#include <functional>
#include <cmath>

#include "Tsl2561LuxValues.h"

namespace I2c
{

class Tsl2561LuxCalculator
{
public:
	Tsl2561LuxCalculator(bool isChipScale=false);
	Tsl2561LuxValues ComputeLux(uint16_t rawAdc0Value, uint16_t rawAdc1Value) const;

private:
	typedef std::function<double(double)> calculator_t;

	struct LuxCalculatorThreshold
	{
			double quotientThreshold;
			calculator_t calculateVisibleSpectrumLux;
	};

	static constexpr size_t NUM_THRESHOLD_MAPPINGS = 7;

	typedef std::array<LuxCalculatorThreshold, NUM_THRESHOLD_MAPPINGS> threshold_mapping_t;

	static const threshold_mapping_t CHIP_SCALE_THRESHOLD_MAPPING;
	static const threshold_mapping_t NON_CHIP_SCALE_THRESHOLD_MAPPING;

private:
	const threshold_mapping_t *m_thresholdMapping;
};

} // namespace I2c
