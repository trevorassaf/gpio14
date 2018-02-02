#include "I2c/Devices/Tsl2561LuxMeter/Tsl2561ThresholdHalfWord.h"

namespace I2c
{

Tsl2561ThresholdHalfWord::Tsl2561ThresholdHalfWord(uint16_t halfWord)
	: m_halfWord{halfWord} {}

uint16_t Tsl2561ThresholdHalfWord::GetHalfWord() const
{
		return m_halfWord;
}

void Tsl2561ThresholdHalfWord::SetHalfWord(uint16_t halfWord)
{
		m_halfWord = halfWord;
}

} // namespace I2c
