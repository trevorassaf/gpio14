#include "I2c/Devices/Tsl2561LuxMeter/Tsl2561AdcHalfWord.h"

namespace I2c
{
Tsl2561AdcHalfWord::Tsl2561AdcHalfWord(uint16_t halfWord)
	: m_halfWord{halfWord} {}

void Tsl2561AdcHalfWord::SetHalfWord(uint16_t halfWord)
{
		m_halfWord = halfWord;
}

uint16_t Tsl2561AdcHalfWord::HalfWord() const
{
		return m_halfWord;
}

} // namespace I2c
