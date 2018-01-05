#include "I2c/Registers/ControlRegister.h"

#include <iostream>

#include <utility>

#include "Utils/StlUtils.h"

namespace BitIndex
{
namespace Model
{
constexpr size_t I2C_ENABLE = 0;
constexpr size_t RX_INTR = 1;
constexpr size_t TX_INTR = 2;
constexpr size_t DONE_INTR = 3;
constexpr size_t START_TRANSFER = 4;
constexpr size_t CLEAR_FIFO = 5;
constexpr size_t READ_TRANSFER = 6;
} // namespace Model

namespace Mmio
{
constexpr size_t I2C_ENABLE = 15;
constexpr size_t RX_INTR = 10;
constexpr size_t TX_INTR = 9;
constexpr size_t DONE_INTR = 8;
constexpr size_t START_TRANSFER = 7;
constexpr size_t CLEAR_FIFO = 4;
constexpr size_t READ_TRANSFER = 0; 
} // namespace Mmio
} // namespace BitIndex

namespace I2c
{
ControlRegister::ControlRegister() : m_bits{} {}

ControlRegister::ControlRegister(std::bitset<NUM_BITS> bits) : m_bits{std::move(bits)} {}

ControlRegister::ControlRegister(
		bool i2cEnabled,
		bool rxInteruptEnabled,
		bool txInteruptEnabled,
		bool doneInteruptEnabled,
		bool startTransfer,
		bool clearFifo,
		bool readTransfer)
: m_bits{Utils::to_bitset(
			i2cEnabled,
			rxInteruptEnabled,
			txInteruptEnabled,
			doneInteruptEnabled,
			startTransfer,
			clearFifo,
			readTransfer)}
{}

bool ControlRegister::IsI2cEnabled() const { return m_bits.test(BitIndex::Model::I2C_ENABLE); }
bool ControlRegister::IsRxInteruptEnabled() const { return m_bits.test(BitIndex::Model::RX_INTR); }
bool ControlRegister::IsTxInteruptEnabled() const { return m_bits.test(BitIndex::Model::TX_INTR); }
bool ControlRegister::IsDoneInteruptEnabled() const { return m_bits.test(BitIndex::Model::DONE_INTR); }
bool ControlRegister::IsStartTransfer() const { return m_bits.test(BitIndex::Model::START_TRANSFER); }
bool ControlRegister::IsClearFifo() const { return m_bits.test(BitIndex::Model::CLEAR_FIFO); }
bool ControlRegister::IsReadTransfer() const { return m_bits.test(BitIndex::Model::READ_TRANSFER); }

uint32_t ControlRegister::ToMmioRegister() const
{
		uint32_t mmioRegister = 0;

		mmioRegister |= IsI2cEnabled() << BitIndex::Mmio::I2C_ENABLE;
		mmioRegister |= IsRxInteruptEnabled() << BitIndex::Mmio::RX_INTR;
		mmioRegister |= IsTxInteruptEnabled() << BitIndex::Mmio::TX_INTR;
		mmioRegister |= IsDoneInteruptEnabled() << BitIndex::Mmio::DONE_INTR;
		mmioRegister |= IsStartTransfer() << BitIndex::Mmio::START_TRANSFER;
		mmioRegister |= IsClearFifo() << BitIndex::Mmio::CLEAR_FIFO;
		mmioRegister |= IsReadTransfer() << BitIndex::Mmio::READ_TRANSFER;

		return mmioRegister;
}

std::ostream& operator<<(std::ostream &stream, const ControlRegister &reg)
{
		stream << "I2CEN: " << reg.IsI2cEnabled() << " (I2c enabled)" << std::endl
					 << "INTR:  " << reg.IsRxInteruptEnabled() << " (Rx interupts enabled)" << std::endl
					 << "INTT:  " << reg.IsTxInteruptEnabled() << " (Tx interupts enabled)" << std::endl
					 << "INTD:  " << reg.IsDoneInteruptEnabled() << " (Done interupts enabled)" << std::endl
					 << "ST:    " << reg.IsStartTransfer() << " (Start transfer)" << std::endl
					 << "CLEAR: " << reg.IsClearFifo() << " (Clear fifo)" << std::endl
					 << "READ:  " << reg.IsReadTransfer() << " (Read transfer)" << std::endl;
		return stream;
}

ControlRegisterBuilder::ControlRegisterBuilder() : m_bits{} {}

ControlRegisterBuilder& ControlRegisterBuilder::SetI2cEnabled(bool value)
{
		m_bits[BitIndex::Model::I2C_ENABLE] = value;
		return *this;
}

ControlRegisterBuilder& ControlRegisterBuilder::SetRxInteruptEnabled(bool value)
{
		m_bits[BitIndex::Model::RX_INTR] = value;
		return *this;
}

ControlRegisterBuilder& ControlRegisterBuilder::SetTxInteruptEnabled(bool value)
{
		m_bits[BitIndex::Model::TX_INTR] = value;
		return *this;
}

ControlRegisterBuilder& ControlRegisterBuilder::SetDoneInteruptEnabled(bool value)
{
		m_bits[BitIndex::Model::DONE_INTR] = value;
		return *this;
}

ControlRegisterBuilder& ControlRegisterBuilder::SetStartTransfer(bool value)
{
		m_bits[BitIndex::Model::START_TRANSFER] = value;
		return *this;
}

ControlRegisterBuilder& ControlRegisterBuilder::SetClearFifo(bool value)
{
		m_bits[BitIndex::Model::CLEAR_FIFO] = value;
		return *this;
}

ControlRegisterBuilder& ControlRegisterBuilder::SetReadTransfer(bool value)
{
		m_bits[BitIndex::Model::READ_TRANSFER] = value;
		return *this;
}

ControlRegisterBuilder& ControlRegisterBuilder::FromMmioRegister(uint32_t bits)
{
		SetI2cEnabled(bits & BitIndex::Mmio::I2C_ENABLE);
		SetRxInteruptEnabled(bits & BitIndex::Mmio::RX_INTR);
		SetTxInteruptEnabled(bits & BitIndex::Mmio::TX_INTR);
		SetDoneInteruptEnabled(bits & BitIndex::Mmio::DONE_INTR);
		SetStartTransfer(bits & BitIndex::Mmio::START_TRANSFER);
		SetClearFifo(bits & BitIndex::Mmio::CLEAR_FIFO);
		SetReadTransfer(bits & BitIndex::Mmio::READ_TRANSFER);

		return *this;
}

ControlRegister ControlRegisterBuilder::Build() const
{
		return ControlRegister{m_bits};
}

} // namespace I2c
