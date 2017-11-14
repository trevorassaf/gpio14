#include "I2c/Registers/StatusRegister.h"

#include "Utils/StlUtils.h"

namespace
{
enum class Index : size_t
{
		CLOCK_STRETCH_TIMEOUT = 0,
		ACK_ERROR = 1,
		FIFO_FULL = 2,
		FIFO_EMPTY = 3,
		FIFO_CONTAINS_DATA = 4,
		FIFO_CAN_ACCEPT_DATA = 5,
		FIFO_NEEDS_READING = 6,
		FIFO_NEEDS_WRITING = 7,
		TRANSFER_DONE = 8,
		TRANSFER_ACTIVE = 9
};
} // namespace

namespace I2c
{
StatusRegister::StatusRegister() : m_bits{} {}

StatusRegister::StatusRegister(std::bitset<NUM_BITS> bits) : m_bits{std::move(bits)} {}

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
	return m_bits.test(static_cast<size_t>(Index::CLOCK_STRETCH_TIMEOUT));
}

bool StatusRegister::IsAckError() const
{
  return m_bits.test(static_cast<size_t>(Index::ACK_ERROR));
}

bool StatusRegister::IsFifoFull() const
{
  return m_bits.test(static_cast<size_t>(Index::FIFO_FULL));
}

bool StatusRegister::IsFifoEmpty() const
{
  return m_bits.test(static_cast<size_t>(Index::FIFO_EMPTY));
}

bool StatusRegister::IsFifoContainsData() const
{
  return m_bits.test(static_cast<size_t>(Index::FIFO_CONTAINS_DATA));
}

bool StatusRegister::IsFifoCanAcceptData() const
{
  return m_bits.test(static_cast<size_t>(Index::FIFO_CAN_ACCEPT_DATA));
}

bool StatusRegister::IsFifoNeedsReading() const
{
  return m_bits.test(static_cast<size_t>(Index::FIFO_NEEDS_READING));
}

bool StatusRegister::IsFifoNeedsWriting() const
{
  return m_bits.test(static_cast<size_t>(Index::FIFO_NEEDS_WRITING));
}

bool StatusRegister::IsTransferDone() const
{
  return m_bits.test(static_cast<size_t>(Index::TRANSFER_DONE));
}

bool StatusRegister::IsTransferActive() const
{
  return m_bits.test(static_cast<size_t>(Index::TRANSFER_ACTIVE));
}

StatusRegisterBuilder::StatusRegisterBuilder() : m_bits{} {}

StatusRegisterBuilder &StatusRegisterBuilder::SetClockStretchTimeout(bool value)
{
		m_bits[static_cast<size_t>(Index::CLOCK_STRETCH_TIMEOUT)] = value;
		return *this;
}

StatusRegisterBuilder &StatusRegisterBuilder::SetAckError(bool value)
{
		m_bits[static_cast<size_t>(Index::ACK_ERROR)] = value;
		return *this;
}

StatusRegisterBuilder &StatusRegisterBuilder::SetFifoFull(bool value)
{
		m_bits[static_cast<size_t>(Index::FIFO_FULL)] = value;
		return *this;
}

StatusRegisterBuilder &StatusRegisterBuilder::SetFifoEmpty(bool value)
{
		m_bits[static_cast<size_t>(Index::FIFO_EMPTY)] = value;
		return *this;
}

StatusRegisterBuilder &StatusRegisterBuilder::SetFifoContainsData(bool value)
{
		m_bits[static_cast<size_t>(Index::FIFO_CONTAINS_DATA)] = value;
		return *this;
}

StatusRegisterBuilder &StatusRegisterBuilder::SetFifoCanAcceptData(bool value)
{
		m_bits[static_cast<size_t>(Index::FIFO_CAN_ACCEPT_DATA)] = value;
		return *this;
}

StatusRegisterBuilder &StatusRegisterBuilder::SetFifoNeedsReading(bool value)
{
		m_bits[static_cast<size_t>(Index::FIFO_NEEDS_READING)] = value;
		return *this;
}

StatusRegisterBuilder &StatusRegisterBuilder::SetFifoNeedsWriting(bool value)
{
		m_bits[static_cast<size_t>(Index::FIFO_NEEDS_WRITING)] = value;
		return *this;
}

StatusRegisterBuilder &StatusRegisterBuilder::SetTransferDone(bool value)
{
		m_bits[static_cast<size_t>(Index::TRANSFER_DONE)] = value;
		return *this;
}

StatusRegisterBuilder &StatusRegisterBuilder::SetTransferActive(bool value)
{
		m_bits[static_cast<size_t>(Index::TRANSFER_ACTIVE)] = value;
		return *this;
}

StatusRegister StatusRegisterBuilder::Build() const
{
		return StatusRegister{m_bits};
}

} // namespace I2c
