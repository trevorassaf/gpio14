#pragma once

#include <memory>

#include "I2c/Registers/BscMasterRegisters.h"
#include "I2c/Registers/ClockDivideRegister.h"
#include "I2c/Registers/ClockStretchTimeoutRegister.h"
#include "I2c/Registers/ControlRegister.h"
#include "I2c/Registers/DataDelayRegister.h"
#include "I2c/Registers/DataFifoRegister.h"
#include "I2c/Registers/DataLengthRegister.h"
#include "I2c/Registers/SlaveAddressRegister.h"
#include "I2c/Registers/StatusRegister.h"

namespace I2c
{

class BscMaster
{
public:
	BscMaster(std::unique_ptr<BscMasterRegisters> registers);

	ControlRegister ReadControlRegister() const;
	StatusRegister ReadStatusRegister() const;
	DataLengthRegister ReadDataLengthRegister() const;
	SlaveAddressRegister ReadSlaveAddressRegister() const;
	DataFifoRegister ReadDataFifoRegister() const;
	ClockDivideRegister ReadClockDivideRegister() const;
	DataDelayRegister ReadDataDelayRegister() const;
	ClockStretchTimeoutRegister ReadClockStretchTimeoutRegister() const;

private:
	std::unique_ptr<BscMasterRegisters> m_registers;
};

} // namespace I2c
