#pragma once

#include <cstdint>

#include "Tsl2561Register.h"
#include "Tsl2561InterruptControlMode.h"
#include "Tsl2561InterruptPersistenceLevel.h"

namespace I2c
{

class Tsl2561InterruptControlRegister : public Tsl2561Register
{
public:
	Tsl2561InterruptControlRegister();
	
	Tsl2561InterruptControlRegister(
			Tsl2561InterruptControlMode mode,
			Tsl2561InterruptPersistenceLevel level);

	Tsl2561InterruptControlRegister(uint8_t bits);

	Tsl2561InterruptControlMode GetControlMode() const;
	Tsl2561InterruptPersistenceLevel GetPersistenceLevel() const;

	void SetControlMode(Tsl2561InterruptControlMode controlMode);
	void SetPersistenceLevel(Tsl2561InterruptPersistenceLevel persistenceLevel);

	uint8_t Bits() const override;

private:
	uint8_t m_bits;
};

} // namespace I2c
