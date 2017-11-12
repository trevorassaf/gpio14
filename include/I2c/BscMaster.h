#pragma once

#include <memory>

#include "I2c/BscMasterRegisters.h"

namespace I2c
{

class BscMaster
{
public:
	BscMaster(std::unique_ptr<BscMasterRegisters> registers);

private:
	std::unique_ptr<BscMasterRegisters> m_registers;
};

} // namespace I2c
