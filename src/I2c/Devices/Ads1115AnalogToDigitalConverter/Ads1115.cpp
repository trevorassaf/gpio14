#include "I2c/Devices/Ads1115AnalogToDigitalConverter/Ads1115.h"

#include <cassert>
#include <chrono>
#include <iostream>
#include <thread>

#include "glog/logging.h"

#include "I2c/I2cException.h"

namespace
{
constexpr uint8_t kSensorConfigAddress = 0x01;
constexpr uint8_t kSensorConfigFirstByte = 0xc3; // c-f for 4 analog channels
constexpr uint8_t kSensorConfigSecondByte = 0x83;
constexpr uint8_t kSensorConversionAddress = 0x00;
constexpr size_t kSensorConfigFirstByteShift = 4;
const std::chrono::seconds kSleepInterval{1};

uint8_t MakeFirstConfigByte(I2c::Ads1115Channel channel)
{
  return kSensorConfigFirstByte | ((static_cast<uint8_t>(channel) << kSensorConfigFirstByteShift));
}

} // namespace

namespace I2c
{

Ads1115::Ads1115(I2cClient *i2c) : i2c_{i2c} {}

Ads1115::Ads1115(Ads1115 &&other)
{
  StealResources(&other);
}

Ads1115& Ads1115::operator=(Ads1115 &&other)
{
  if (this != &other)
  {
    StealResources(&other);
  }

  return *this;
}

Ads1115::~Ads1115()
{
  i2c_ = nullptr;
}

bool Ads1115::Read(Ads1115Channel channel, uint16_t *out_reading)
{
  assert(out_reading);

  try
  {
    uint8_t config_buffer[3];
    config_buffer[0] = kSensorConfigAddress;
    config_buffer[1] = MakeFirstConfigByte(channel);
    config_buffer[2] = kSensorConfigSecondByte;
    i2c_->Write(config_buffer, sizeof(config_buffer));

    std::this_thread::sleep_for(kSleepInterval);

    i2c_->Write((uint8_t*)&kSensorConversionAddress, sizeof(kSensorConversionAddress));

    i2c_->Read((uint8_t*)out_reading, sizeof(*out_reading));
    uint8_t msb_byte = (*out_reading >> 8) & 0xFF;
    uint8_t lsb_byte = *out_reading & 0xFF;
    *out_reading = (lsb_byte << 8) | msb_byte;
  }
  catch (const I2cException &e)
  {
    LOG(ERROR) << "Failed during Ads1115 read channel operation";
    return false;
  }

  return true;
}

void Ads1115::StealResources(Ads1115 *other)
{
  assert(other);
  i2c_ = other->i2c_;
  other->i2c_ = nullptr;
}

} // namespace I2c
