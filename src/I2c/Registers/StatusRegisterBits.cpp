#include "I2c/Registers/StatusRegisterBits.h"

namespace
{
constexpr size_t CLOCK_STRETCH_OFFSET = 9;
constexpr size_t ACK_ERROR_OFFSET = 8;
constexpr size_t FIFO_FULL_OFFSET = 7;
constexpr size_t FIFO_EMPTY_OFFSET = 6;
constexpr size_t FIFO_CONTAINS_DATA_OFFSET = 5;
constexpr size_t FIFO_CAN_ACCEPT_DATA_OFFSET = 4;
constexpr size_t FIFO_NEEDS_READING_OFFSET = 3;
constexpr size_t FIFO_NEEDS_WRITING_OFFSET = 2;
constexpr size_t FIFO_TRANSFER_DONE_OFFSET = 1;
constexpr size_t FIFO_TRANSFER_ACTIVE_OFFSET = 0;
} // namespace

namespace I2c
{

size_t StatusRegisterBits::GetClockStretchOffset() const
{
  return CLOCK_STRETCH_OFFSET;
}

size_t StatusRegisterBits::GetAckErrorOffset() const
{
  return ACK_ERROR_OFFSET;
}

size_t StatusRegisterBits::GetFifoFullOffset() const
{
  return FIFO_FULL_OFFSET;
}

size_t StatusRegisterBits::GetFifoEmptyOffset() const
{
  return FIFO_EMPTY_OFFSET;
}

size_t StatusRegisterBits::GetFifoContainsDataOffset() const
{
  return FIFO_CONTAINS_DATA_OFFSET;
}

size_t StatusRegisterBits::GetFifoCanAcceptDataOffset() const
{
  return FIFO_CAN_ACCEPT_DATA_OFFSET;
}

size_t StatusRegisterBits::GetFifoNeedsReadingOffset() const
{
  return FIFO_NEEDS_READING_OFFSET;
}

size_t StatusRegisterBits::GetFifoNeedsWritingOffset() const
{
  return FIFO_NEEDS_WRITING_OFFSET;
}

size_t StatusRegisterBits::GetTransferDoneOffset() const
{
  return FIFO_TRANSFER_DONE_OFFSET;
}

size_t StatusRegisterBits::GetTransferActiveOffset() const
{
  return FIFO_TRANSFER_ACTIVE_OFFSET;
}

} // namespace I2c
