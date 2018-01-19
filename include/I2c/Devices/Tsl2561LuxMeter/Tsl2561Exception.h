#pragma once

#include <cstdint>

namespace I2c
{

enum class Tsl2561ErrorType : uint8_t
{
		FAILED_TO_POWER_UP,
		CLIENT_DISCONNECT,
};

class Tsl2561Exception
{
public:
	Tsl2561Exception(Tsl2561ErrorType type) : m_type{type} {}
	Tsl2561ErrorType GetType() const { return m_type; }

private:
	Tsl2561ErrorType m_type;
};

} // namespace I2c
