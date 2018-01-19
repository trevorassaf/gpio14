#pragma once

#include <cstdint>

#include "Tsl2561IntegrationTime.h"
#include "Tsl2561Register.h"

namespace I2c
{

class Tsl2561TimingRegister : public Tsl2561Register
{
public:
	Tsl2561TimingRegister(
			bool isLowGain,
			bool beginManualIntegrationCycle,
			Tsl2561IntegrationTime integrationTime);
	Tsl2561TimingRegister(uint8_t bits=0);

	// 'True' means low gain. 'False' means high gain.
	bool IsLowGain() const;
	bool IsStartManualIntegrationCycle() const;
	Tsl2561IntegrationTime GetIntegrationTime() const;

	void SetIsLowGain(bool isLowGain);
	void SetStartManualIntegrationCycle(bool isCycleStart);
	void SetIntegrationTime(Tsl2561IntegrationTime integrationTime);

	uint8_t Bits() const override;

private:
	uint8_t m_bits;
};

} // namespace I2c
