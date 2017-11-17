#include "I2c/Registers/StatusRegister.h"

#include "Utils/StlUtils.h"

namespace BitIndex
{
namespace Model
{
constexpr size_t CLOCK_STRETCH_TIMEOUT = 0;
constexpr size_t ACK_ERROR = 1;
constexpr size_t FIFO_FULL = 2;
constexpr size_t FIFO_EMPTY = 3;
constexpr size_t FIFO_CONTAINS_DATA = 4;
constexpr size_t FIFO_CAN_ACCEPT_DATA = 5;
constexpr size_t FIFO_NEEDS_READING = 6;
constexpr size_t FIFO_NEEDS_WRITING = 7;
constexpr size_t TRANSFER_DONE = 8;
constexpr size_t TRANSFER_ACTIVE = 9;
} // namespace Model

namespace Mmio
{
constexpr size_t CLOCK_STRETCH = 9;
constexpr size_t ACK_ERROR = 8;
constexpr size_t FIFO_FULL = 7;
constexpr size_t FIFO_EMPTY = 6;
constexpr size_t FIFO_CONTAINS_DATA = 5;
constexpr size_t FIFO_CAN_ACCEPT_DATA = 4;
constexpr size_t FIFO_NEEDS_READING = 3;
constexpr size_t FIFO_NEEDS_WRITING = 2;
constexpr size_t TRANSFER_DONE = 1;
constexpr size_t TRANSFER_ACTIVE = 0;
} // namespace Mmio
} // namespace BitIndex

namespace I2c
{
StatusRegister::StatusRegister() : m_bits{} {}

StatusRegister::StatusRegister(std::bitset<NUM_BITS> bits) : m_bits{std::move(bits)} {}

StatusRegister::StatusRegister(uint32_t bits) : StatusRegister{std::bitset<NUM_BITS>{bits}} {}

StatusRegister::StatusRegister(
	bool clockStretchTimeout,
	bool ackError,
	bool fifoFull,
	bool fifoEmpty,
	bool fifoContainsData,
	bool fifoCanAcceptData,
	bool fifoNeedsReading,
	bool fifoNeedsWriting,
	bool transferDone,
	bool transferActive)
: m_bits{Utils::to_bitset(
		clockStretchTimeout,
		ackError,
		fifoFull,
		fifoEmpty,
		fifoContainsData,
		fifoCanAcceptData,
		fifoNeedsReading,
		fifoNeedsWriting,
		transferDone,
		transferActive)} {}

bool StatusRegister::IsClockStretchTimeout() const
{
	return m_bits.test(BitIndex::Model::CLOCK_STRETCH_TIMEOUT);
}

bool StatusRegister::IsAckError() const
{
  return m_bits.test(BitIndex::Model::ACK_ERROR);
}

bool StatusRegister::IsFifoFull() const
{
  return m_bits.test(BitIndex::Model::FIFO_FULL);
}

bool StatusRegister::IsFifoEmpty() const
{
  return m_bits.test(BitIndex::Model::FIFO_EMPTY);
}

bool StatusRegister::IsFifoContainsData() const
{
  return m_bits.test(BitIndex::Model::FIFO_CONTAINS_DATA);
}

bool StatusRegister::IsFifoCanAcceptData() const
{
  return m_bits.test(BitIndex::Model::FIFO_CAN_ACCEPT_DATA);
}

bool StatusRegister::IsFifoNeedsReading() const
{
  return m_bits.test(BitIndex::Model::FIFO_NEEDS_READING);
}

bool StatusRegister::IsFifoNeedsWriting() const
{
  return m_bits.test(BitIndex::Model::FIFO_NEEDS_WRITING);
}

bool StatusRegister::IsTransferDone() const
{
  return m_bits.test(BitIndex::Model::TRANSFER_DONE);
}

bool StatusRegister::IsTransferActive() const
{
  return m_bits.test(BitIndex::Model::TRANSFER_ACTIVE);
}

StatusRegisterBuilder::StatusRegisterBuilder() : m_bits{} {}

StatusRegisterBuilder &StatusRegisterBuilder::SetClockStretchTimeout(bool value)
{
		m_bits[BitIndex::Model::CLOCK_STRETCH_TIMEOUT] = value;
		return *this;
}

StatusRegisterBuilder &StatusRegisterBuilder::SetAckError(bool value)
{
		m_bits[BitIndex::Model::ACK_ERROR] = value;
		return *this;
}

StatusRegisterBuilder &StatusRegisterBuilder::SetFifoFull(bool value)
{
		m_bits[BitIndex::Model::FIFO_FULL] = value;
		return *this;
}

StatusRegisterBuilder &StatusRegisterBuilder::SetFifoEmpty(bool value)
{
		m_bits[BitIndex::Model::FIFO_EMPTY] = value;
		return *this;
}

StatusRegisterBuilder &StatusRegisterBuilder::SetFifoContainsData(bool value)
{
		m_bits[BitIndex::Model::FIFO_CONTAINS_DATA] = value;
		return *this;
}

StatusRegisterBuilder &StatusRegisterBuilder::SetFifoCanAcceptData(bool value)
{
		m_bits[BitIndex::Model::FIFO_CAN_ACCEPT_DATA] = value;
		return *this;
}

StatusRegisterBuilder &StatusRegisterBuilder::SetFifoNeedsReading(bool value)
{
		m_bits[BitIndex::Model::FIFO_NEEDS_READING] = value;
		return *this;
}

StatusRegisterBuilder &StatusRegisterBuilder::SetFifoNeedsWriting(bool value)
{
		m_bits[BitIndex::Model::FIFO_NEEDS_WRITING] = value;
		return *this;
}

StatusRegisterBuilder &StatusRegisterBuilder::SetTransferDone(bool value)
{
		m_bits[BitIndex::Model::TRANSFER_DONE] = value;
		return *this;
}

StatusRegisterBuilder &StatusRegisterBuilder::SetTransferActive(bool value)
{
		m_bits[BitIndex::Model::TRANSFER_ACTIVE] = value;
		return *this;
}

StatusRegisterBuilder &StatusRegisterBuilder::FromMmioRegister(uint32_t bits)
{
		SetClockStretchTimeout(bits & BitIndex::Mmio::CLOCK_STRETCH);
		SetAckError(bits & BitIndex::Mmio::ACK_ERROR);
		SetFifoFull(bits & BitIndex::Mmio::FIFO_FULL);
		SetFifoEmpty(bits & BitIndex::Mmio::FIFO_EMPTY);
		SetFifoContainsData(bits & BitIndex::Mmio::FIFO_CONTAINS_DATA);
		SetFifoCanAcceptData(bits & BitIndex::Mmio::FIFO_CAN_ACCEPT_DATA);
		SetFifoNeedsReading(bits & BitIndex::Mmio::FIFO_NEEDS_READING);
		SetFifoNeedsWriting(bits & BitIndex::Mmio::FIFO_NEEDS_WRITING);
		SetTransferDone(bits & BitIndex::Mmio::TRANSFER_DONE);
		SetTransferActive(bits & BitIndex::Mmio::TRANSFER_ACTIVE);
		
		return *this;
}

StatusRegister StatusRegisterBuilder::Build() const
{
		return StatusRegister{m_bits};
}

} // namespace I2c
