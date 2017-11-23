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

void BscMaster::WriteControlRegister(const ControlRegister &reg)
{
		*m_registers->GetControlRegister() = reg.ToMmioRegister();
}

void BscMaster::WriteStatusRegister(const StatusRegister &reg)
{
		*m_registers->GetStatusRegister() = reg.ToMmioRegister();
}

void BscMaster::WriteDataLengthRegister(const DataLengthRegister &reg)
{
		*m_registers->GetDataLengthRegister() = reg.ToMmioRegister();
}

void BscMaster::WriteSlaveAddressRegister(const SlaveAddressRegister &reg)
{
		*m_registers->GetSlaveAddressRegister() = reg.ToMmioRegister();
}

void BscMaster::WriteDataFifoRegister(const DataFifoRegister &reg)
{
		*m_registers->GetDataFifoRegister() = reg.ToMmioRegister();
}

void BscMaster::WriteClockDivideRegister(const ClockDivideRegister &reg)
{
		*m_registers->GetClockDivideRegister() = reg.ToMmioRegister();
}

void BscMaster::WriteDataDelayRegister(const DataDelayRegister &reg)
{
		*m_registers->GetDataDelayRegister() = reg.ToMmioRegister();
}

void BscMaster::WriteClockStretchTimeoutRegister(const ClockStretchTimeoutRegister &reg)
{
		*m_registers->GetClockStretchTimeoutRegister() = reg.ToMmioRegister();
}

} // namespace I2c
