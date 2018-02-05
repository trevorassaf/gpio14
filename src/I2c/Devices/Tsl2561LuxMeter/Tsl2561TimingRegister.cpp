#include "I2c/Devices/Tsl2561LuxMeter/Tsl2561TimingRegister.h"

#include <cstdint>
#include <cstdlib>

#include "Utils/BitUtils.h"

namespace
{
constexpr size_t LOW_GAIN_BIT_SHIFT = 4;
constexpr size_t START_MANUAL_INTEGRATION_CYCLE_BIT_SHIFT = 3;
constexpr size_t INTEGRATION_TIME_BIT_SHIFT = 0;

constexpr uint8_t LOW_GAIN_MASK = (1 << LOW_GAIN_BIT_SHIFT);
constexpr uint8_t START_MANUAL_INTEGRATION_CYCLE_MASK = (1 << START_MANUAL_INTEGRATION_CYCLE_BIT_SHIFT);
constexpr uint8_t INTEGRATION_TIME_MASK = 0b00000011;
} // namespace

using Utils::BitUtils;

namespace I2c
{

Tsl2561TimingRegister::Tsl2561TimingRegister() : m_bits{0} {}

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
		return m_bits & LOW_GAIN_MASK;
}

bool Tsl2561TimingRegister::IsStartManualIntegrationCycle() const
{
		return m_bits & START_MANUAL_INTEGRATION_CYCLE_MASK;
}

Tsl2561IntegrationTime Tsl2561TimingRegister::GetIntegrationTime() const
{
		return static_cast<Tsl2561IntegrationTime>(m_bits & INTEGRATION_TIME_MASK);
}

void Tsl2561TimingRegister::SetIsLowGain(bool isLowGain)
{
		m_bits = BitUtils::SetBitWithMask(
				m_bits,
				isLowGain,
				LOW_GAIN_MASK,
				LOW_GAIN_BIT_SHIFT);
}

void Tsl2561TimingRegister::SetStartManualIntegrationCycle(bool isCycleStart)
{
		m_bits = BitUtils::SetBitWithMask(
				m_bits,
				isCycleStart,
				START_MANUAL_INTEGRATION_CYCLE_MASK,
				START_MANUAL_INTEGRATION_CYCLE_BIT_SHIFT);
}

void Tsl2561TimingRegister::SetIntegrationTime(Tsl2561IntegrationTime integrationTime)
{
		m_bits = BitUtils::SetByteWithMask(
				m_bits,
				static_cast<uint8_t>(integrationTime),
				INTEGRATION_TIME_MASK,
				INTEGRATION_TIME_BIT_SHIFT);
}

uint8_t Tsl2561TimingRegister::Bits() const
{
		return m_bits;
}

} // namespace I2c
