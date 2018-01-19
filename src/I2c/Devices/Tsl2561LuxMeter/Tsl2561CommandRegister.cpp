#include "I2c/Devices/Tsl2561LuxMeter/Tsl2561CommandRegister.h"

#include <cstdint>

#include "Utils/BitUtils.h"

using Utils::BitUtils;

namespace
{
constexpr uint8_t COMMAND_REGISTER_MASK_AND_VALUE = (1 << 7);
constexpr uint8_t CLEAR_INTERRUPT_MASK_AND_VALUE = (1 << 6);
constexpr uint8_t WORD_PROTOCOL_MASK_AND_VALUE = (1 << 5);
constexpr uint8_t BLOCK_PROTOCOL_MASK_AND_VALUE = (1 << 4);
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
		return m_bits & CLEAR_INTERRUPT_MASK_AND_VALUE;
}

bool Tsl2561CommandRegister::IsWordProtocol() const
{
		return m_bits & WORD_PROTOCOL_MASK_AND_VALUE;
}

bool Tsl2561CommandRegister::IsBlockProtocol() const
{
		return m_bits & BLOCK_PROTOCOL_MASK_AND_VALUE;
}

Tsl2561Address Tsl2561CommandRegister::GetAddress() const
{
		return static_cast<Tsl2561Address>(m_bits & ADDRESS_MASK);
}

void Tsl2561CommandRegister::SetClearInterrupt(bool clearInterrupt)
{
		uint8_t value = (clearInterrupt) ? CLEAR_INTERRUPT_MASK_AND_VALUE : 0;
		m_bits = BitUtils::SetByteWithMask(
				m_bits, value, CLEAR_INTERRUPT_MASK_AND_VALUE);
}

void Tsl2561CommandRegister::SetWordProtocol(bool isWordProtocol)
{
		uint8_t value = (isWordProtocol) ? WORD_PROTOCOL_MASK_AND_VALUE : 0;
		m_bits = BitUtils::SetByteWithMask(
				m_bits, value, WORD_PROTOCOL_MASK_AND_VALUE);
}

void Tsl2561CommandRegister::SetBlockProtocol(bool isBlockProtocol)
{
		uint8_t value = (isBlockProtocol) ? BLOCK_PROTOCOL_MASK_AND_VALUE : 0;
		m_bits = BitUtils::SetByteWithMask(
				m_bits, value, BLOCK_PROTOCOL_MASK_AND_VALUE);
}

void Tsl2561CommandRegister::SetAddress(Tsl2561Address address)
{
		m_bits = BitUtils::SetByteWithMask(m_bits, static_cast<uint8_t>(address), ADDRESS_MASK);
}

uint8_t Tsl2561CommandRegister::Bits() const
{
		return m_bits;
}

void Tsl2561CommandRegister::p_SetCommandRegisterBit()
{
		m_bits = BitUtils::SetByteWithMask(
				m_bits, COMMAND_REGISTER_MASK_AND_VALUE, COMMAND_REGISTER_MASK_AND_VALUE);
}

} // namespace I2c
