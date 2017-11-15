#include "I2c/BscMaster.h"

namespace I2c
{
BscMaster::BscMaster(std::unique_ptr<BscMasterRegisters> registers)
	: m_registers{std::move(registers)} {}

ControlRegister BscMaster::ReadControlRegister() const
{
		return (ControlRegisterBuilder{})
			.FromMmioRegister(*m_registers->GetControlRegister())
			.Build();
}

StatusRegister BscMaster::ReadStatusRegister() const
{
		return (StatusRegisterBuilder{})
			.FromMmioRegister(*m_registers->GetStatusRegister())
			.Build();
}

DataLengthRegister BscMaster::ReadDataLengthRegister() const
{
		return (DataLengthRegisterBuilder{})
			.FromMmioRegister(*m_registers->GetStatusRegister())
			.Build();
}

SlaveAddressRegister BscMaster::ReadSlaveAddressRegister() const
{
		return (SlaveAddressRegisterBuilder{})
			.FromMmioRegister(*m_registers->GetSlaveAddressRegister())
			.Build();
}

DataFifoRegister BscMaster::ReadDataFifoRegister() const
{
		return DataFifoRegister{*m_registers->GetDataFifoRegister()};
}

ClockDivideRegister BscMaster::ReadClockDivideRegister() const
{
		return (ClockDivideRegisterBuilder{})
			.FromMmioRegister(*m_registers->GetClockDivideRegister())
			.Build();
}

DataDelayRegister BscMaster::ReadDataDelayRegister() const
{
		return (DataDelayRegisterBuilder{})
			.FromMmioRegister(*m_registers->GetClockDivideRegister())
			.Build();
}

ClockStretchTimeoutRegister BscMaster::ReadClockStretchTimeoutRegister() const
{
		return (ClockStretchTimeoutRegisterBuilder())
			.FromMmioRegister(*m_registers->GetClockStretchTimeoutRegister())
			.Build();
}

} // namespace I2c
