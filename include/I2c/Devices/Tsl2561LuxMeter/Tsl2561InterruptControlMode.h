#pragma once

#include <cstdint>

namespace I2c
{

enum class Tsl2561InterruptControlMode : uint8_t
{
		INTERRUPT_OUTPUT_DISABLED = 0,
		LEVEL_INTERRUPT = 1,
		SMB_ALERT_COMPLIANT = 2,
		TEST_MODE = 3,
};

} // namespace I2c
