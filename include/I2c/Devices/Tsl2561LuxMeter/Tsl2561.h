#pragma once

#include <cstdint>

#include "I2c/I2cClient.h"
#include "Tsl2561Address.h"
#include "Tsl2561InterruptControlMode.h"
#include "Tsl2561InterruptPersistenceLevel.h"
#include "Tsl2561IntegrationTime.h"
#include "Tsl2561LuxValues.h"
#include "Tsl2561CommandRegister.h"
#include "Tsl2561ControlRegister.h"
#include "Tsl2561IdRegister.h"
#include "Tsl2561InterruptControlRegister.h"
#include "Tsl2561TimingRegister.h"
#include "Tsl2561LuxCalculator.h"
#include "Tsl2561Core.h"

namespace I2c
{

class Tsl2561
{
public:
	/**
	 * Powers up device.
	 */
	Tsl2561(I2cClient *i2cClient);

	/**
	 * Powers down device. Does not close I2c client.
	 */
	~Tsl2561();

	/**
	 * "Timing Register" control
	 */
	void SetHighGain();
	void SetLowGain();

	void StartIntegrationCycle();
	void StopIntegrationCycle();

	void SetIntegrationTime(Tsl2561IntegrationTime time);

	/**
	 * "Interrupts Threshold Register" control.
	 */
	void SetAdcLowThreshold(uint16_t threshold);
	void SetAdcHighThreshold(uint16_t threshold);

	/**
	 * "Interrupts Control Register" control
	 */
	void SetInterruptControlMode(Tsl2561InterruptControlMode mode);
	void SetInterruptPersistenceLevel(Tsl2561InterruptPersistenceLevel level);

	/**
	 * "ID Register" control
	 */
	Tsl2561IdRegister ReadId();

	/**
	 * "ADC Channel Data Registers" control
	 */
	Tsl2561LuxValues ReadLux();

	/**
	 * "Command register" control
	 */
	void ClearInterrupt();

private:
	/**
	 * "Control Register" control
	 */
	void p_PowerUp();
	void p_PowerDown();
	bool p_IsPoweredOn();

	void p_SetGain(bool isLowGain);
	void p_StartOrStopIntegrationCycle(bool isStart);

	void p_MaybeWriteAndSaveCommandRegister(const Tsl2561CommandRegister &commandRegister);

private:
	Tsl2561LuxCalculator m_luxCalculator;
	Tsl2561CommandRegister m_commandRegister;
	Tsl2561TimingRegister m_timingRegister;
	Tsl2561InterruptControlRegister m_interruptControlRegister;
	Tsl2561Core m_core;
};

} // namespace I2c
