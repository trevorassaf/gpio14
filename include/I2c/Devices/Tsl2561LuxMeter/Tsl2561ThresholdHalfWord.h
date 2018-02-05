#pragma once

#include <cstdint>

#include "Tsl2561HalfWord.h"

namespace I2c
{

class Tsl2561ThresholdHalfWord : public Tsl2561HalfWord
{
public:
	Tsl2561ThresholdHalfWord();
	Tsl2561ThresholdHalfWord(uint16_t halfWord);
	uint16_t GetHalfWord() const override;
	void SetHalfWord(uint16_t halfWord);

private:
	uint16_t m_halfWord;
};

} // namespace I2c
