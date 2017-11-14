#include "I2c/Registers/ControlRegister.h"

#include <utility>

#include "Utils/StlUtils.h"

namespace
{
enum class Index : size_t
{
		I2C_ENABLED = 0,
		RX_INTERUPTS_ENABLED = 1,
		TX_INTERUPTS_ENABLED = 2,
		DONE_INTERUPTS_ENABLED = 3,
		START_TRANSFER = 4,
		CLEAR_FIFO = 5,
		READ_TRANSFER = 6,
};
} // namespace

namespace I2c
{
ControlRegister::ControlRegister() : m_bits{} {}

ControlRegister::ControlRegister(std::bitset<NUM_BITS> bits) : m_bits{std::move(bits)} {}

ControlRegister::ControlRegister(
		bool i2cEnabled,
		bool rxInteruptsEnabled,
		bool txInteruptsEnabled,
		bool doneInteruptsEnabled,
		bool startTransfer,
		bool clearFifo,
		bool readTransfer)
: m_bits{Utils::to_bitset(
			i2cEnabled,
			rxInteruptsEnabled,
			txInteruptsEnabled,
			doneInteruptsEnabled,
			startTransfer,
			clearFifo,
			readTransfer)}
{}

bool ControlRegister::IsI2cEnabled() const { return m_bits.test(static_cast<size_t>(Index::I2C_ENABLED)); }
bool ControlRegister::IsRxInteruptsEnabled() const { return m_bits.test(static_cast<size_t>(Index::RX_INTERUPTS_ENABLED)); }
bool ControlRegister::IsTxInteruptsEnabled() const { return m_bits.test(static_cast<size_t>(Index::TX_INTERUPTS_ENABLED)); }
bool ControlRegister::IsDoneInteruptsEnabled() const { return m_bits.test(static_cast<size_t>(Index::DONE_INTERUPTS_ENABLED)); }
bool ControlRegister::IsStartTransfer() const { return m_bits.test(static_cast<size_t>(Index::START_TRANSFER)); }
bool ControlRegister::IsClearFifo() const { return m_bits.test(static_cast<size_t>(Index::CLEAR_FIFO)); }
bool ControlRegister::IsReadTransfer() const { return m_bits.test(static_cast<size_t>(Index::READ_TRANSFER)); }

ControlRegisterBuilder::ControlRegisterBuilder() : m_bits{} {}

ControlRegisterBuilder& ControlRegisterBuilder::SetI2cEnabled(bool value)
{
		m_bits[static_cast<size_t>(Index::I2C_ENABLED)] = value;
		return *this;
}

ControlRegisterBuilder& ControlRegisterBuilder::SetRxInteruptsEnabled(bool value)
{
		m_bits[static_cast<size_t>(Index::RX_INTERUPTS_ENABLED)] = value;
		return *this;
}

ControlRegisterBuilder& ControlRegisterBuilder::SetTxInteruptsEnabled(bool value)
{
		m_bits[static_cast<size_t>(Index::TX_INTERUPTS_ENABLED)] = value;
		return *this;
}

ControlRegisterBuilder& ControlRegisterBuilder::SetDoneInteruptsEnabled(bool value)
{
		m_bits[static_cast<size_t>(Index::DONE_INTERUPTS_ENABLED)] = value;
		return *this;
}

ControlRegisterBuilder& ControlRegisterBuilder::SetStartTransfer(bool value)
{
		m_bits[static_cast<size_t>(Index::START_TRANSFER)] = value;
		return *this;
}

ControlRegisterBuilder& ControlRegisterBuilder::SetClearFifo(bool value)
{
		m_bits[static_cast<size_t>(Index::CLEAR_FIFO)] = value;
		return *this;
}

ControlRegisterBuilder& ControlRegisterBuilder::SetReadTransfer(bool value)
{
		m_bits[static_cast<size_t>(Index::READ_TRANSFER)] = value;
		return *this;
}

ControlRegister ControlRegisterBuilder::Build() const
{
		return ControlRegister{m_bits};
}

} // namespace I2c
