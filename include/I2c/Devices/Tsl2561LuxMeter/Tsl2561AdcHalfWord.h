#pragma once

#include <cstdint>

#include "Tsl2561HalfWord.h"

namespace I2c
{
class Tsl2561AdcHalfWord : public Tsl2561HalfWord
{
public:
	Tsl2561AdcHalfWord(uint16_t halfWord=0);
	void SetHalfWord(uint16_t halfWord);
	uint16_t GetHalfWord() const override;

private:
	uint16_t m_halfWord;
};
} // namespace I2c
