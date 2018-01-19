#include "I2c/Devices/Tsl2561LuxMeter/Tsl2561TimingRegister.h"

#include <cstdint>

#include "Utils/BitUtils.h"

constexpr uint8_t LOW_GAIN_MASK_AND_VALUE = (1 << 4);
constexpr uint8_t START_MANUAL_INTEGRATION_CYCLE_MASK_AND_VALUE = (1 << 3);
constexpr uint8_t INTEGRATION_TIME_MASK = 0x00000011;

using Utils::BitUtils;

namespace I2c
{

Tsl2561TimingRegister::Tsl2561TimingRegister(
		bool isLowGain,
		bool startManualIntegrationCycle,
		Tsl2561IntegrationTime integrationTime)
{
		m_bits = 0;
		SetIsLowGain(isLowGain);
		SetStartManualIntegrationCycle(startManualIntegrationCycle);
		SetIntegrationTime(integrationTime);
}

Tsl2561TimingRegister::Tsl2561TimingRegister(uint8_t bits) : m_bits{bits} {}

bool Tsl2561TimingRegister::IsLowGain() const
{
		return m_bits & LOW_GAIN_MASK_AND_VALUE;
}

bool Tsl2561TimingRegister::IsStartManualIntegrationCycle() const
{
		return m_bits & START_MANUAL_INTEGRATION_CYCLE_MASK_AND_VALUE;
}

Tsl2561IntegrationTime Tsl2561TimingRegister::GetIntegrationTime() const
{
		return static_cast<Tsl2561IntegrationTime>(m_bits & INTEGRATION_TIME_MASK);
}

void Tsl2561TimingRegister::SetIsLowGain(bool isLowGain)
{
		m_bits = BitUtils::SetBitWithMask(m_bits, isLowGain, LOW_GAIN_MASK_AND_VALUE);
}

void Tsl2561TimingRegister::SetStartManualIntegrationCycle(bool isCycleStart)
{
		m_bits = BitUtils::SetBitWithMask(
				m_bits, isCycleStart, START_MANUAL_INTEGRATION_CYCLE_MASK_AND_VALUE);
}

void Tsl2561TimingRegister::SetIntegrationTime(Tsl2561IntegrationTime integrationTime)
{
		m_bits = BitUtils::SetByteWithMask(
				m_bits, static_cast<uint8_t>(integrationTime), INTEGRATION_TIME_MASK);
}

uint8_t Tsl2561TimingRegister::Bits() const
{
		return m_bits;
}

} // namespace I2c
