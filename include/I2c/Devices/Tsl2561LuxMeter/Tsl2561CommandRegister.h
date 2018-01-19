#pragma once

#include <cstdint>

#include "I2c/Devices/Tsl2561LuxMeter/Tsl2561Address.h"
#include "I2c/Devices/Tsl2561LuxMeter/Tsl2561Register.h"

namespace I2c
{
class Tsl2561CommandRegister : public Tsl2561Register
{
public:
	Tsl2561CommandRegister();
	Tsl2561CommandRegister(Tsl2561Address address);
	Tsl2561CommandRegister(
			bool clearInterrupt,
			bool wordProtocol,
			bool blockProtocol,
			Tsl2561Address address);

	bool operator==(const Tsl2561CommandRegister &other) const;

	bool IsClearInterrupt() const;
	bool IsWordProtocol() const;
	bool IsBlockProtocol() const;
	Tsl2561Address GetAddress() const;

	void SetClearInterrupt(bool clearInterrupt);
	void SetWordProtocol(bool isWordProtocol);
	void SetBlockProtocol(bool isBlockProtocol);
	void SetAddress(Tsl2561Address address);

	uint8_t Bits() const override;

private:
	void p_SetCommandRegisterBit();

private:
	uint8_t m_bits;
};
} // namespace I2c
