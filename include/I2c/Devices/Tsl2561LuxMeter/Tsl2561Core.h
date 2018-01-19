#pragma once

#include "I2c/I2cClient.h"
#include "Tsl2561Address.h"
#include "Tsl2561PowerControl.h"
#include "Tsl2561IntegrationTime.h"
#include "Tsl2561InterruptControlMode.h"
#include "Tsl2561InterruptControlRegister.h"
#include "Tsl2561InterruptPersistenceLevel.h"
#include "Tsl2561AdcHalfWord.h"
#include "Tsl2561CommandRegister.h"
#include "Tsl2561ControlRegister.h"
#include "Tsl2561IdRegister.h"
#include "Tsl2561TimingRegister.h"
#include "Tsl2561ThresholdHalfWord.h"
#include "Tsl2561HalfWord.h"

namespace I2c
{

class Tsl2561Core
{
public:
	Tsl2561Core(I2cClient *i2c);

	void WriteCommandRegister(const Tsl2561CommandRegister &commandRegister);

	void WriteControlRegister(const Tsl2561ControlRegister &controlRegister);
	Tsl2561ControlRegister ReadControlRegister();

	void WriteTimingRegister(const Tsl2561TimingRegister &timingRegister);

	void WriteLowThresholdHalfWord(const Tsl2561ThresholdHalfWord &threshold);
	void WriteHighThresholdHalfWord(const Tsl2561ThresholdHalfWord &threshold);

	void WriteInterruptControlRegister(
			const Tsl2561InterruptControlRegister &interruptControlRegister);

	Tsl2561IdRegister ReadIdRegister();

	Tsl2561AdcHalfWord ReadAdc0HalfWord();
	Tsl2561AdcHalfWord ReadAdc1HalfWord();

private:
	uint8_t  p_ReadByte();
	uint16_t p_ReadHalfWord();

	void p_WriteTsl2561Register(const Tsl2561Register &tsl2561Register);
	void p_WriteTsl2561HalfWord(const Tsl2561HalfWord &tsl2561HalfWord);

private:
	I2cClient *m_i2c;
};

} // namespace I2c
