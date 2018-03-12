#include "I2c/Devices/Tsl2561LuxMeter/Tsl2561LuxCalculator.h"

#include <array>
#include <cassert>
#include <cmath>
#include <functional>
#include <iostream>

namespace I2c
{
constexpr size_t Tsl2561LuxCalculator::NUM_THRESHOLD_MAPPINGS;

const Tsl2561LuxCalculator::threshold_mapping_t Tsl2561LuxCalculator::CHIP_SCALE_THRESHOLD_MAPPING =
{
		LuxCalculatorThreshold{0.52, [] (double adc0, double adc1) { return 0.0315  * adc0 - 0.0593  * adc0 * std::pow(adc1/adc0, 1.4); }},
		LuxCalculatorThreshold{0.65, [] (double adc0, double adc1) { return 0.0229  * adc0 - 0.0291  * adc1; }},
		LuxCalculatorThreshold{0.80, [] (double adc0, double adc1) { return 0.0157  * adc0 - 0.0180  * adc1; }},
		LuxCalculatorThreshold{1.30, [] (double adc0, double adc1) { return 0.00338 * adc0 - 0.00260 * adc1; }},
};

const Tsl2561LuxCalculator::threshold_mapping_t Tsl2561LuxCalculator::NON_CHIP_SCALE_THRESHOLD_MAPPING =
{
		LuxCalculatorThreshold{0.50, [] (double adc0, double adc1) { return 0.0304  * adc0 - 0.0620  * adc0 * std::pow(adc1/adc0, 1.4); }},
		LuxCalculatorThreshold{0.61, [] (double adc0, double adc1) { return 0.0224  * adc0 - 0.031   * adc1; }},
		LuxCalculatorThreshold{0.80, [] (double adc0, double adc1) { return 0.0128  * adc0 - 0.0153  * adc1; }},
		LuxCalculatorThreshold{1.30, [] (double adc0, double adc1) { return 0.00146 * adc0 - 0.00112 * adc1; }},
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
  std::cout << "Adc 0 value: " << adc0Value  << std::endl;
  std::cout << "Adc 1 value: " << adc1Value  << std::endl;

		Tsl2561LuxValues values;
		values.irSpectrumLux = adc1Value;

		double luxQuotient = adc1Value / adc0Value;
    std::cout << "Lux quotient: " << luxQuotient << std::endl;

		assert(m_thresholdMapping);

		for (const auto& threshold : *m_thresholdMapping)
		{
        std::cout << "Quotient threshold: " << threshold.quotientThreshold << std::endl;
				if (luxQuotient <= threshold.quotientThreshold)
				{
						values.visibleSpectrumLux =
							threshold.calculateVisibleSpectrumLux(adc0Value, adc1Value);
						return values;
				}
		}

		values.visibleSpectrumLux = 0;
		return values;
}

} // namespace I2c
