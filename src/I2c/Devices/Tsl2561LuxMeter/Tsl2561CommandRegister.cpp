#include "I2c/Devices/Tsl2561LuxMeter/Tsl2561CommandRegister.h"

#include <cstdint>
#include <cstdlib>

#include "Utils/BitUtils.h"

using Utils::BitUtils;

namespace
{
constexpr size_t COMMAND_REGISTER_BIT_SHIFT = 7;
constexpr size_t CLEAR_INTERRUPT_BIT_SHIFT = 6;
constexpr size_t WORD_PROTOCOL_BIT_SHIFT = 5;
constexpr size_t BLOCK_PROTOCOL_BIT_SHIFT = 4;
constexpr size_t ADDRESS_BIT_SHIFT = 0;

constexpr uint8_t COMMAND_REGISTER_MASK = (1 << COMMAND_REGISTER_BIT_SHIFT);
constexpr uint8_t CLEAR_INTERRUPT_MASK = (1 << CLEAR_INTERRUPT_BIT_SHIFT);
constexpr uint8_t WORD_PROTOCOL_MASK = (1 << WORD_PROTOCOL_BIT_SHIFT);
constexpr uint8_t BLOCK_PROTOCOL_MASK = (1 << BLOCK_PROTOCOL_BIT_SHIFT);
constexpr uint8_t ADDRESS_MASK = 0b00001111;
} // namespace

namespace I2c
{

Tsl2561CommandRegister::Tsl2561CommandRegister()
{
		p_SetCommandRegisterBit();
		SetClearInterrupt(false);
		SetWordProtocol(false);
		SetBlockProtocol(false);

		// Note that we don't set "address" here because this is a command register
		// and "address" is ignored anyway.
}

Tsl2561CommandRegister::Tsl2561CommandRegister(
		bool isClearInterrupt,
		bool isWordProtocol,
		bool isBlockProtocol,
		Tsl2561Address address)
{
		p_SetCommandRegisterBit();
		SetClearInterrupt(isClearInterrupt);
		SetWordProtocol(isWordProtocol);
		SetBlockProtocol(isBlockProtocol);
		SetAddress(address);
}

Tsl2561CommandRegister::Tsl2561CommandRegister(Tsl2561Address address)
	: Tsl2561CommandRegister{false, false, false, address} {}

bool Tsl2561CommandRegister::operator==(const Tsl2561CommandRegister &other) const
{
		return m_bits == other.m_bits;
}

bool Tsl2561CommandRegister::IsClearInterrupt() const
{
		return m_bits & CLEAR_INTERRUPT_MASK;
}

bool Tsl2561CommandRegister::IsWordProtocol() const
{
		return m_bits & WORD_PROTOCOL_MASK;
}

bool Tsl2561CommandRegister::IsBlockProtocol() const
{
		return m_bits & BLOCK_PROTOCOL_MASK;
}

Tsl2561Address Tsl2561CommandRegister::GetAddress() const
{
		return static_cast<Tsl2561Address>(m_bits & ADDRESS_MASK);
}

void Tsl2561CommandRegister::SetClearInterrupt(bool clearInterrupt)
{
		uint8_t value = static_cast<uint8_t>(clearInterrupt);
		m_bits = BitUtils::SetByteWithMask(
				m_bits, value, CLEAR_INTERRUPT_MASK, CLEAR_INTERRUPT_BIT_SHIFT);
}

void Tsl2561CommandRegister::SetWordProtocol(bool isWordProtocol)
{
		uint8_t value = static_cast<uint8_t>(isWordProtocol);
		m_bits = BitUtils::SetBitWithMask(m_bits, value, WORD_PROTOCOL_MASK, WORD_PROTOCOL_BIT_SHIFT);
}

void Tsl2561CommandRegister::SetBlockProtocol(bool isBlockProtocol)
{
		uint8_t value = static_cast<uint8_t>(isBlockProtocol);
		m_bits = BitUtils::SetByteWithMask(
				m_bits, value, BLOCK_PROTOCOL_MASK, BLOCK_PROTOCOL_BIT_SHIFT);
}

void Tsl2561CommandRegister::SetAddress(Tsl2561Address address)
{
		m_bits = BitUtils::SetByteWithMask(
				m_bits, static_cast<uint8_t>(address), ADDRESS_MASK, ADDRESS_BIT_SHIFT);
}

uint8_t Tsl2561CommandRegister::Bits() const
{
		return m_bits;
}

void Tsl2561CommandRegister::p_SetCommandRegisterBit()
{
		m_bits = BitUtils::SetBitWithMask(
				m_bits, 1, COMMAND_REGISTER_MASK, COMMAND_REGISTER_BIT_SHIFT);
}

} // namespace I2c
