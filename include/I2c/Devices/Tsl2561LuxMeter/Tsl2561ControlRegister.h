#pragma once

#include <cstdint>

#include "Tsl2561PowerControl.h"
#include "Tsl2561Register.h"

namespace I2c
{

class Tsl2561ControlRegister : public Tsl2561Register
{
public:
	Tsl2561ControlRegister();
	Tsl2561ControlRegister(uint8_t bits);
	Tsl2561ControlRegister(Tsl2561PowerControl powerControl);
	Tsl2561PowerControl GetPowerControl() const;
	void SetPowerControl(Tsl2561PowerControl powerControl);
	bool IsPoweredOn() const;
	uint8_t Bits() const override;

private:
	Tsl2561PowerControl m_powerControl;
};

} // namespace I2c
