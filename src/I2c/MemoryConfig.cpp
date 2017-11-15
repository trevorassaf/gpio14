#include "I2c/MemoryConfig.h"

namespace
{
constexpr size_t CONTROL_REGISTER_OFFSET = 0x00;
constexpr size_t STATUS_REGISTER_OFFSET = 0x04;
constexpr size_t DATA_LENGTH_REGISTER_OFFSET = 0x08;
constexpr size_t SLAVE_ADDRESS_REGISTER_OFFSET = 0x0C;
constexpr size_t DATA_FIFO_REGISTER_OFFSET = 0x10;
constexpr size_t CLOCK_DIVIDER_REGISTER_OFFSET = 0x14;
constexpr size_t DATA_DELAY_REGISTER_OFFSET = 0x18;
constexpr size_t CLOCK_STRETCH_TIMEOUT_REGISTER_OFFSET = 0x1C;
} // namespace

namespace I2c
{
size_t MemoryConfig::GetControlOffset() const { return CONTROL_REGISTER_OFFSET; }
size_t MemoryConfig::GetStatusOffset() const { return STATUS_REGISTER_OFFSET; }
size_t MemoryConfig::GetDataLengthOffset() const { return DATA_LENGTH_REGISTER_OFFSET; }
size_t MemoryConfig::GetSlaveAddressOffset() const { return SLAVE_ADDRESS_REGISTER_OFFSET; }
size_t MemoryConfig::GetDataFifoOffset() const { return DATA_FIFO_REGISTER_OFFSET; }
size_t MemoryConfig::GetClockDivideOffset() const { return CLOCK_DIVIDER_REGISTER_OFFSET; }
size_t MemoryConfig::GetDataDelayOffset() const { return DATA_DELAY_REGISTER_OFFSET; }
size_t MemoryConfig::GetClockStretchTimeoutOffset() const { return CLOCK_STRETCH_TIMEOUT_REGISTER_OFFSET; }
} // namespace I2c
