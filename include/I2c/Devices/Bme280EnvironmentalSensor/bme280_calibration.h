#pragma once

namespace I2c
{
struct bme280_temp_calib_t
{
		uint16_t dig1;
		int16_t  dig2;
		int16_t  dig3;
} __attribute__((packed));

struct bme280_pres_calib_t
{
		uint16_t dig1;
		int16_t  dig[8];
} __attribute__((packed));

struct bme280_hum_calib_top_half_t
{
		uint8_t dig1;
} __attribute__((packed));

struct bme280_hum_calib_bottom_half_t
{
		int16_t dig2;
		uint8_t dig3;
		int16_t dig4;
		int16_t dig5;
		int8_t  dig6;
} __attribute__((packed));

struct bme280_hum_calib_t
{
		bme280_hum_calib_top_half_t top;
		bme280_hum_calib_bottom_half_t bottom;
} __attribute__((packed));
} // namespace I2c
