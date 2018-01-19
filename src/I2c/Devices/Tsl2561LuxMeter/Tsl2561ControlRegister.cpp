#include "I2c/Devices/Tsl2561LuxMeter/Tsl2561ControlRegister.h"
#include "I2c/Devices/Tsl2561LuxMeter/Tsl2561PowerControl.h"

namespace I2c
{

Tsl2561ControlRegister::Tsl2561ControlRegister() : m_powerControl{Tsl2561PowerControl::POWER_DOWN} {}

Tsl2561ControlRegister::Tsl2561ControlRegister(uint8_t bits) : m_powerControl{static_cast<Tsl2561PowerControl>(bits)} {}

Tsl2561ControlRegister::Tsl2561ControlRegister(Tsl2561PowerControl powerControl)
	: m_powerControl{powerControl} {}

Tsl2561PowerControl Tsl2561ControlRegister::GetPowerControl() const
{
		return m_powerControl;
}

bool Tsl2561ControlRegister::IsPoweredOn() const
{
		return m_powerControl != Tsl2561PowerControl::POWER_DOWN;
}

uint8_t Tsl2561ControlRegister::Bits() const
{
		return static_cast<uint8_t>(m_powerControl);
}

} // namespace I2c
