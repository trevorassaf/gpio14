#include "I2c/Devices/Tsl2561LuxMeter/Tsl2561ThresholdRegister.h"

namespace I2c
{

Tsl2561ThresholdRegister::Tsl2561ThresholdRegister(uint8_t byte) : m_bits{byte} {}

uint8_t Tsl2561ThresholdRegister::Bits() const { return m_bits; }

} // namespace I2c
