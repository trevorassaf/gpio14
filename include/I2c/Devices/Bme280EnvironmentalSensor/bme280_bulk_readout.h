#pragma once

namespace I2c
{
struct bme280_bulk_readout_t
{
		uint32_t pressure;
		uint32_t temperature;
		uint16_t humidity;
} __attribute__((packed));
} // namespace I2c
