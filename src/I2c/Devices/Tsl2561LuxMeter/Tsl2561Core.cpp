#include "I2c/Devices/Tsl2561LuxMeter/Tsl2561Core.h"

namespace I2c
{

Tsl2561Core::Tsl2561Core(I2cClient *i2c) : m_i2c{i2c} {}

void Tsl2561Core::WriteCommandRegister(const Tsl2561CommandRegister &commandRegister)
{
		p_WriteTsl2561Register(commandRegister);
}

void Tsl2561Core::WriteControlRegister(const Tsl2561ControlRegister &controlRegister)
{
		p_WriteTsl2561Register(controlRegister);
}

Tsl2561ControlRegister Tsl2561Core::ReadControlRegister()
{
		return Tsl2561ControlRegister{p_ReadByte()};
}

void Tsl2561Core::WriteTimingRegister(const Tsl2561TimingRegister &timingRegister)
{
		p_WriteTsl2561Register(timingRegister);
}

void Tsl2561Core::WriteLowThresholdHalfWord(const Tsl2561ThresholdHalfWord &threshold)
{
		p_WriteTsl2561HalfWord(threshold);
}

void Tsl2561Core::WriteHighThresholdHalfWord(const Tsl2561ThresholdHalfWord &threshold)
{
		p_WriteTsl2561HalfWord(threshold);
}

void Tsl2561Core::WriteInterruptControlRegister(
		const Tsl2561InterruptControlRegister &interruptControlRegister)
{
		p_WriteTsl2561Register(interruptControlRegister);
}

Tsl2561IdRegister Tsl2561Core::ReadIdRegister()
{
		return Tsl2561IdRegister{p_ReadByte()};
}

Tsl2561AdcHalfWord Tsl2561Core::ReadAdc0HalfWord()
{
		return Tsl2561AdcHalfWord{p_ReadHalfWord()};
}

Tsl2561AdcHalfWord Tsl2561Core::ReadAdc1HalfWord()
{
		return Tsl2561AdcHalfWord{p_ReadHalfWord()};
}

uint8_t Tsl2561Core::p_ReadByte()
{
		uint8_t buffer = 0;
		m_i2c->Read(&buffer, 1);
		return buffer;
}

uint16_t Tsl2561Core::p_ReadHalfWord()
{
		uint16_t buffer = 0;
		m_i2c->Read(reinterpret_cast<uint8_t*>(&buffer), 2);
		return buffer;
}

void Tsl2561Core::p_WriteTsl2561Register(const Tsl2561Register &tsl2561Register)
{
		uint8_t buffer = tsl2561Register.Bits();
		m_i2c->Write(&buffer, 1);
}

void Tsl2561Core::p_WriteTsl2561HalfWord(const Tsl2561HalfWord &tsl2561HalfWord)
{
		uint16_t buffer = tsl2561HalfWord.GetHalfWord();
		m_i2c->Write(reinterpret_cast<uint8_t*>(&buffer), 2);
}

} // namespace I2c
