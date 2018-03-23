#include "I2c/Devices/Tsl2561LuxMeter/Tsl2561LuxCalculator.h"

#include <array>
#include <cassert>
#include <cmath>
#include <functional>
#include <iostream>

namespace I2c
{
constexpr size_t Tsl2561LuxCalculator::NUM_THRESHOLD_MAPPINGS;

const Tsl2561LuxCalculator::threshold_mapping_t Tsl2561LuxCalculator::NON_CHIP_SCALE_THRESHOLD_MAPPING =
{
		LuxCalculatorThreshold{0.125, [] (double adcQuotient) { return 0.0304  - 0.0272  * adcQuotient; }},
		LuxCalculatorThreshold{0.250, [] (double adcQuotient) { return 0.0325  - 0.0440  * adcQuotient; }},
		LuxCalculatorThreshold{0.375, [] (double adcQuotient) { return 0.0371  - 0.0544  * adcQuotient; }},
		LuxCalculatorThreshold{0.500, [] (double adcQuotient) { return 0.0381  - 0.0624  * adcQuotient; }},
		LuxCalculatorThreshold{0.610, [] (double adcQuotient) { return 0.0224  - 0.0310  * adcQuotient; }},
		LuxCalculatorThreshold{0.800, [] (double adcQuotient) { return 0.0128  - 0.0153  * adcQuotient; }},
		LuxCalculatorThreshold{1.300, [] (double adcQuotient) { return 0.00146 - 0.00112 * adcQuotient; }},
};

const Tsl2561LuxCalculator::threshold_mapping_t Tsl2561LuxCalculator::CHIP_SCALE_THRESHOLD_MAPPING =
{
		LuxCalculatorThreshold{0.13, [] (double adcQuotient) { return 0.0315  - 0.0262  * adcQuotient; }},
		LuxCalculatorThreshold{0.26, [] (double adcQuotient) { return 0.0337  - 0.0430  * adcQuotient; }},
		LuxCalculatorThreshold{0.39, [] (double adcQuotient) { return 0.0363  - 0.0529  * adcQuotient; }},
		LuxCalculatorThreshold{0.52, [] (double adcQuotient) { return 0.0392  - 0.0605  * adcQuotient; }},
		LuxCalculatorThreshold{0.65, [] (double adcQuotient) { return 0.0229  - 0.0291  * adcQuotient; }},
		LuxCalculatorThreshold{0.80, [] (double adcQuotient) { return 0.00157 - 0.00180 * adcQuotient; }},
		LuxCalculatorThreshold{1.30, [] (double adcQuotient) { return 0.00338 - 0.00260 * adcQuotient; }},
};

Tsl2561LuxCalculator::Tsl2561LuxCalculator(bool isChipScale)
	: m_thresholdMapping{nullptr}
{
		m_thresholdMapping = (isChipScale)
			? &CHIP_SCALE_THRESHOLD_MAPPING
			: &NON_CHIP_SCALE_THRESHOLD_MAPPING;
}

Tsl2561LuxValues Tsl2561LuxCalculator::ComputeLux(
		uint16_t adc0Value, uint16_t adc1Value) const
{
		Tsl2561LuxValues values;
		values.irSpectrumLux = adc1Value;

		double adcQuotient = static_cast<double>(adc1Value) / adc0Value;

		assert(m_thresholdMapping);

		for (const auto& threshold : *m_thresholdMapping)
		{
				if (adcQuotient <= threshold.quotientThreshold)
				{
						values.visibleSpectrumLux =
							threshold.calculateVisibleSpectrumLux(adcQuotient) * adc0Value;
						return values;

				}
		}

		values.visibleSpectrumLux = 0;
		return values;
}

} // namespace I2c
