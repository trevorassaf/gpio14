#pragma once

#include <cstdlib>

namespace Bme280
{
constexpr size_t HUM_LSB = 0xFE;
constexpr size_t HUM_MSB = 0xFD;
constexpr size_t TEMP_XLSB = 0xFC;
constexpr size_t TEMP_LSB = 0xFB;
constexpr size_t TEMP_MSB = 0xFA;
constexpr size_t PRES_XLSB = 0xF9;
constexpr size_t PRES_LSB = 0xF8;
constexpr size_t PRES_MSB = 0xF7;

// Yes... 0xF6 is skipped
constexpr size_t CONFIG = 0xF5;
constexpr size_t CTRL_MEAS = 0xF4;
constexpr size_t STATUS = 0xF3;
constexpr size_t CTRL_HUM = 0xF2;

constexpr size_t CALIB_41 = 0xF0;
// Compute CALIB_(26,41) manually
constexpr size_t CALIB_26 = 0xE1;

constexpr size_t RESET = 0xE0

constexpr size_t CHIP_ID = 0xD0

constexpr size_t CALIB_25 = 0xA1;
// Compute CALIB_(00,25) manually
constexpr size_t CALIB_00 = 0x88;

} // namespace Bme280
