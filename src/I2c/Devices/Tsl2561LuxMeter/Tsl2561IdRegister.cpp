#include "I2c/Devices/Tsl2561LuxMeter/Tsl2561IdRegister.h"

#include <cstdlib>

#include "Utils/BitUtils.h"

using Utils::BitUtils;

namespace
{
constexpr uint8_t PART_NUMBER_MASK = 0b11110000;
constexpr uint8_t REVISION_ID_MASK = 0b00001111;
constexpr size_t PART_NUMBER_BIT_SHIFT = 4;
constexpr size_t REVISION_ID_BIT_SHIFT = 0;
} // namespace

namespace I2c
{
Tsl2561IdRegister::Tsl2561IdRegister(uint8_t partNumber, uint8_t revisionId)
{
		m_bits = 0;
		SetPartNumber(partNumber);
		SetRevisionId(revisionId);
}

Tsl2561IdRegister::Tsl2561IdRegister(uint8_t bits) : m_bits{bits} {}

uint8_t Tsl2561IdRegister::GetPartNumber() const
{
		return (m_bits & PART_NUMBER_MASK) >> PART_NUMBER_BIT_SHIFT;
}

uint8_t Tsl2561IdRegister::GetRevisionId() const
{
		return (m_bits & REVISION_ID_MASK) >> REVISION_ID_BIT_SHIFT;
}

void Tsl2561IdRegister::SetPartNumber(uint8_t partNumber)
{
		m_bits = BitUtils::SetByteWithMask(m_bits, partNumber, PART_NUMBER_MASK);
}

void Tsl2561IdRegister::SetRevisionId(uint8_t revisionId)
{
		m_bits = BitUtils::SetByteWithMask(m_bits, revisionId, REVISION_ID_MASK);
}

uint8_t Tsl2561IdRegister::Bits() const
{
		return m_bits;
}

} // namespace I2c
