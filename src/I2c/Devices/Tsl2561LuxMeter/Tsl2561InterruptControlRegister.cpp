#include "I2c/Devices/Tsl2561LuxMeter/Tsl2561InterruptControlRegister.h"

#include <cstdlib>

#include "Utils/BitUtils.h"

using Utils::BitUtils;

namespace
{
constexpr uint8_t CONTROL_MODE_MASK          = 0b00110000;
constexpr uint8_t PERSISTENCE_LEVEL_MASK     = 0b00001111;
constexpr size_t CONTROL_MODE_BIT_SHIFT      = 4;
constexpr size_t PERSISTENCE_LEVEL_BIT_SHIFT = 0;
} // namespace

namespace I2c
{

Tsl2561InterruptControlRegister::Tsl2561InterruptControlRegister(
		Tsl2561InterruptControlMode mode,
		Tsl2561InterruptPersistenceLevel level)
{
		m_bits = 0;
		SetControlMode(mode);
		SetPersistenceLevel(level);
}

Tsl2561InterruptControlRegister::Tsl2561InterruptControlRegister(uint8_t bits)
	: m_bits{bits} {}

Tsl2561InterruptControlMode Tsl2561InterruptControlRegister::GetControlMode() const
{
		uint8_t controlModeBits = m_bits & CONTROL_MODE_MASK;
		return static_cast<Tsl2561InterruptControlMode>(controlModeBits >> CONTROL_MODE_BIT_SHIFT);
}

Tsl2561InterruptPersistenceLevel Tsl2561InterruptControlRegister::GetPersistenceLevel() const
{
		uint8_t persistenceLevelBits = m_bits & PERSISTENCE_LEVEL_MASK;
		return static_cast<Tsl2561InterruptPersistenceLevel>(persistenceLevelBits >> PERSISTENCE_LEVEL_BIT_SHIFT);
}

void Tsl2561InterruptControlRegister::SetControlMode(
		Tsl2561InterruptControlMode controlMode)
{
		m_bits = BitUtils::SetByteWithMask(
				m_bits,
				static_cast<uint8_t>(controlMode),
				CONTROL_MODE_MASK,
				CONTROL_MODE_BIT_SHIFT);
}

void Tsl2561InterruptControlRegister::SetPersistenceLevel(
		Tsl2561InterruptPersistenceLevel persistenceLevel)
{
		m_bits = BitUtils::SetByteWithMask(
				m_bits,
				static_cast<uint8_t>(persistenceLevel),
				PERSISTENCE_LEVEL_MASK,
				PERSISTENCE_LEVEL_BIT_SHIFT);
}

uint8_t Tsl2561InterruptControlRegister::Bits() const
{
		return m_bits;
}

} // namespace I2c
