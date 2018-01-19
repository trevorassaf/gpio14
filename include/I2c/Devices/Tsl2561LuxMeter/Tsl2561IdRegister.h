#pragma once

#include <cstdint>

#include "Tsl2561Register.h"

namespace I2c
{
class Tsl2561IdRegister : public Tsl2561Register
{
public:
	Tsl2561IdRegister(uint8_t partNumber, uint8_t revisionId);
	Tsl2561IdRegister(uint8_t bits);
	
	uint8_t GetPartNumber() const;
	uint8_t GetRevisionId() const;

	void SetPartNumber(uint8_t partNumber);
	void SetRevisionId(uint8_t revisionId);

	uint8_t Bits() const override;

private:
	uint8_t m_bits;
};
} // namespace I2c
