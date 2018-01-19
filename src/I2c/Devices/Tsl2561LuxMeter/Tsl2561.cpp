#include "I2c/Devices/Tsl2561LuxMeter/Tsl2561.h"

#include <iostream>

#include "I2c/Devices/Tsl2561LuxMeter/Tsl2561Exception.h"
#include "I2c/Devices/Tsl2561LuxMeter/Tsl2561ThresholdHalfWord.h"

namespace I2c
{

Tsl2561::Tsl2561(I2cClient *i2cClient)
	: m_core{i2cClient},
	  m_luxCalculator{},
		m_commandRegister{},
		m_timingRegister{},
		m_interruptControlRegister{}
{
		p_PowerUp();

		if (!p_IsPoweredOn())
		{
				std::cout << "Tsl2561 failed to power on" << std::endl;
				throw Tsl2561Exception{Tsl2561ErrorType::FAILED_TO_POWER_UP};
		}
}

Tsl2561::~Tsl2561()
{
		p_PowerDown();

		if (p_IsPoweredOn())
		{
				std::cout << "Tsl2561 failed to power off" << std::endl;
		}
}

void Tsl2561::SetHighGain()
{
		p_SetGain(false);
}

void Tsl2561::SetLowGain()
{
		p_SetGain(true);
}

void Tsl2561::StartIntegrationCycle()
{
		p_StartOrStopIntegrationCycle(true);
}

void Tsl2561::StopIntegrationCycle()
{
		p_StartOrStopIntegrationCycle(false);
}

void Tsl2561::SetIntegrationTime(Tsl2561IntegrationTime time)
{
		p_MaybeWriteAndSaveCommandRegister(
				Tsl2561CommandRegister{Tsl2561Address::TIMING});
		m_timingRegister.SetIntegrationTime(time);
		m_core.WriteTimingRegister(m_timingRegister);
}

void Tsl2561::SetAdcLowThreshold(uint16_t threshold)
{
		Tsl2561CommandRegister commandRegister;
		commandRegister.SetWordProtocol(true);
		commandRegister.SetAddress(Tsl2561Address::THRESHLOWLOW);
		p_MaybeWriteAndSaveCommandRegister(commandRegister);

		m_core.WriteLowThresholdHalfWord(Tsl2561ThresholdHalfWord{threshold});
}

void Tsl2561::SetAdcHighThreshold(uint16_t threshold)
{
		Tsl2561CommandRegister commandRegister;
		commandRegister.SetWordProtocol(true);
		commandRegister.SetAddress(Tsl2561Address::THRESHHIGHLOW);
		p_MaybeWriteAndSaveCommandRegister(commandRegister);

		m_core.WriteHighThresholdHalfWord(Tsl2561ThresholdHalfWord{threshold});
}

void Tsl2561::SetInterruptControlMode(Tsl2561InterruptControlMode mode)
{
		p_MaybeWriteAndSaveCommandRegister(Tsl2561CommandRegister{Tsl2561Address::INTERRUPT});
		m_interruptControlRegister.SetControlMode(mode);
		m_core.WriteInterruptControlRegister(m_interruptControlRegister);
}

void Tsl2561::SetInterruptPersistenceLevel(Tsl2561InterruptPersistenceLevel level)
{
		p_MaybeWriteAndSaveCommandRegister(Tsl2561CommandRegister{Tsl2561Address::INTERRUPT});
		m_interruptControlRegister.SetPersistenceLevel(level);
		m_core.WriteInterruptControlRegister(m_interruptControlRegister);
}

Tsl2561IdRegister Tsl2561::ReadId()
{
		p_MaybeWriteAndSaveCommandRegister(Tsl2561CommandRegister{Tsl2561Address::ID});
		return m_core.ReadIdRegister();
}

Tsl2561LuxValues Tsl2561::ReadLux()
{
		Tsl2561CommandRegister commandRegister;
		commandRegister.SetWordProtocol(true);
		commandRegister.SetAddress(Tsl2561Address::DATA0LOW);
		p_MaybeWriteAndSaveCommandRegister(commandRegister);
		Tsl2561AdcHalfWord adc0Value = m_core.ReadAdc0HalfWord();

		commandRegister.SetAddress(Tsl2561Address::DATA1LOW);
		p_MaybeWriteAndSaveCommandRegister(commandRegister);
		Tsl2561AdcHalfWord adc1Value = m_core.ReadAdc1HalfWord();

		return m_luxCalculator.ComputeLux(adc0Value.HalfWord(), adc1Value.HalfWord());
}

void Tsl2561::ClearInterrupt()
{
		m_commandRegister.SetClearInterrupt(true);
		p_MaybeWriteAndSaveCommandRegister(m_commandRegister);
		m_commandRegister.SetClearInterrupt(false);
}

void Tsl2561::p_PowerUp()
{
		p_MaybeWriteAndSaveCommandRegister(
				Tsl2561CommandRegister{Tsl2561Address::CONTROL});
		Tsl2561ControlRegister controlRegister{Tsl2561PowerControl::POWER_UP};
		m_core.WriteControlRegister(controlRegister);
}

void Tsl2561::p_PowerDown()
{
		p_MaybeWriteAndSaveCommandRegister(
				Tsl2561CommandRegister{Tsl2561Address::CONTROL});
		Tsl2561ControlRegister controlRegister{Tsl2561PowerControl::POWER_DOWN};
		m_core.WriteControlRegister(controlRegister);
}

bool Tsl2561::p_IsPoweredOn()
{
		p_MaybeWriteAndSaveCommandRegister(
				Tsl2561CommandRegister{Tsl2561Address::CONTROL});
		Tsl2561ControlRegister controlRegister = m_core.ReadControlRegister();
		return controlRegister.IsPoweredOn();
}

void Tsl2561::p_SetGain(bool isLowGain)
{
		p_MaybeWriteAndSaveCommandRegister(
				Tsl2561CommandRegister{Tsl2561Address::TIMING});
		m_timingRegister.SetIsLowGain(isLowGain);
		m_core.WriteTimingRegister(m_timingRegister);
}

void Tsl2561::p_StartOrStopIntegrationCycle(bool isStart)
{
		p_MaybeWriteAndSaveCommandRegister(
				Tsl2561CommandRegister{Tsl2561Address::TIMING});
		m_timingRegister.SetStartManualIntegrationCycle(isStart);
		m_core.WriteTimingRegister(m_timingRegister);
}

void Tsl2561::p_MaybeWriteAndSaveCommandRegister(const Tsl2561CommandRegister &commandRegister)
{
		if (commandRegister == m_commandRegister)
		{
				return;
		}

		m_core.WriteCommandRegister(commandRegister);
		m_commandRegister = commandRegister;
}

} // namespace I2c
