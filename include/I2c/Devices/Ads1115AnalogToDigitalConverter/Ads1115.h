#ifndef _I2C_DEVICES_ADS1115ANALOGTODIGITALCONVERTER_ADS1115_H_
#define _I2C_DEVICES_ADS1115ANALOGTODIGITALCONVERTER_ADS1115_H_

#include <cstdint>

#include "Ads1115Channel.h"
#include "I2c/I2cClient.h"

namespace I2c
{
class Ads1115
{
public:
  Ads1115(I2cClient *i2c);
  Ads1115(Ads1115 &&other);
  Ads1115& operator=(Ads1115 &&other);
  ~Ads1115();
  bool Read(Ads1115Channel channel, uint16_t *out_reading);

private:
  void StealResources(Ads1115 *other);

private:
  Ads1115(const Ads1115 &other) = delete;
  Ads1115& operator=(const Ads1115 &other) = delete;

private:
  I2cClient *i2c_;
};
} // namespace I2c

#endif // _I2C_DEVICES_ADS1115ANALOGTODIGITALCONVERTER_ADS1115_H_
