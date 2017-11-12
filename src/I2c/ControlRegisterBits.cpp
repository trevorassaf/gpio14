#include "I2c/ControlRegisterBits.h"

namespace 
{
constexpr size_t I2C_ENABLE_OFFSET = 15;
constexpr size_t RX_INTR_OFFSET = 10;
constexpr size_t TX_INTR_OFFSET = 9;
constexpr size_t DONE_INTR_OFFSET = 8;
constexpr size_t START_TRANSFER_OFFSET = 7;
constexpr size_t CLEAR_FIFO_OFFSET = 4;
constexpr size_t READ_TRANSFER_OFFSET = 0; 
} // namespace

namespace I2c
{
size_t ControlRegisterBits::GetI2cEnableOffset() const { return I2C_ENABLE_OFFSET; }
size_t ControlRegisterBits::GetRxIntrOffset() const { return RX_INTR_OFFSET; }
size_t ControlRegisterBits::GetTxIntrOffset() const { return TX_INTR_OFFSET; }
size_t ControlRegisterBits::GetDoneIntrOffset() const { return DONE_INTR_OFFSET; }
size_t ControlRegisterBits::GetStartTransferOffset() const { return START_TRANSFER_OFFSET; }
size_t ControlRegisterBits::GetClearFifoOffset() const { return CLEAR_FIFO_OFFSET; }
size_t ControlRegisterBits::GetReadTransferOffset() const { return READ_TRANSFER_OFFSET; }
} // namespace I2c
