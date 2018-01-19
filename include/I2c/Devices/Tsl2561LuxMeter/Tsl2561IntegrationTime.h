#pragma once

namespace I2c
{

enum class Tsl2561IntegrationTime : uint8_t
{
		INTEGRATION_TIME_13_7_MS = 0,
		INTEGRATION_TIME_101_MS = 1,
		INEGRATION_TIME_402_MS = 2,
		INTEGRATION_TIME_MANUAL = 3,
};

} // namespace I2c
