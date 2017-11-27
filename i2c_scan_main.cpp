#include <chrono>
#include <iostream>
#include <memory>
#include <thread>
#include <utility>

#include "I2c/BscMaster.h"
#include "I2c/Registers/BscMasterRegisters.h"
#include "I2c/Registers/ControlRegister.h"
#include "I2c/Registers/DataFifoRegister.h"
#include "I2c/Registers/DataLengthRegister.h"
#include "I2c/Registers/SlaveAddressRegister.h"
#include "I2c/Registers/StatusRegister.h"
#include "I2c/MemoryConfig.h"
#include "Memory/MmioBcm2835MemorySegment.h"
#include "Memory/MmioConfig.h"

using namespace std::chrono_literals;

using I2c::BscMasterRegisters;
using I2c::BscMaster;
using I2c::ControlRegister;
using I2c::ControlRegisterBuilder;
using I2c::SlaveAddressRegister;
using I2c::StatusRegister;
using I2c::StatusRegisterBuilder;
using I2c::DataFifoRegister;
using I2c::DataLengthRegister;
using I2c::MemoryConfig;
using Memory::MmioBcm2835MemorySegment;
using Memory::MmioConfig;

constexpr uint8_t I2C_MAX_ADDRESS = 0x7F;

int main(int argc, const char **argv)
{
		MemoryConfig memoryConfig;
		auto mmioConfig = MmioConfig::MakeI2c1Config();
		auto mmioSegment = std::make_unique<MmioBcm2835MemorySegment>(&mmioConfig);
		auto bscMasterRegisters = std::make_unique<BscMasterRegisters>(std::move(mmioSegment), &memoryConfig);
		auto bscMaster = std::make_unique<BscMaster>(std::move(bscMasterRegisters));

		// Enable BSC Master 1 I2c registers
		ControlRegisterBuilder controlRegisterBuilder;
		ControlRegister controlRegister = controlRegisterBuilder
			.SetI2cEnabled(true)
			.Build();

		bscMaster->WriteControlRegister(controlRegister);

		// Prepare register values to be used later. We will "ping" I2c slaves by sending
		// 0x00 to all possible I2c slave addresses and listening for acks.
		ControlRegister startTransferControlRegister = controlRegisterBuilder
			.SetStartTransfer(true)
			.SetReadTransfer(false)
			.Build();

		ControlRegister stopTransferControlRegister = controlRegisterBuilder
			.SetStartTransfer(false)
			.Build();

		StatusRegisterBuilder statusRegisterBuilder;
		StatusRegister clearStatusRegister = statusRegisterBuilder
			.SetClearStatusBits()
			.Build();

		DataFifoRegister dataFifoRegister{0x00};
		DataLengthRegister dataLengthRegister{1};

		// Scan I2c address range
		for (uint8_t addr = 0; addr < I2C_MAX_ADDRESS; ++addr)
		{
				// "Ping" I2c slave at this address
				SlaveAddressRegister slaveAddressRegister{addr};
				bscMaster->WriteSlaveAddressRegister(slaveAddressRegister);
				bscMaster->WriteDataFifoRegister(dataFifoRegister);
				bscMaster->WriteDataLengthRegister(dataLengthRegister);
				bscMaster->WriteControlRegister(startTransferControlRegister);

				StatusRegister pingResult;
				size_t numSleeps = 5;
				do
				{
						// Sleep long enough for BscMaster to flush the I2c buffer and for
						// slave to respond. 10ms is arbitrary...
						std::this_thread::sleep_for(10ms);
						pingResult = bscMaster->ReadStatusRegister();
				} while (pingResult.IsTransferDone() && --numSleeps >= 0);

				// Check for an ACK. If we received one, then the current I2c address
				// refers to a slave. Report this result to the user.
				std::cout << "Slave status for I2c address " << std::hex << addr
									<< ": " << (pingResult.IsAckError()) ? "DOWN" : "UP";
		
				// Prepare for next write/read cycle. This involves clering the status
				// register flags and stopping the current transfer.
				bscMaster->WriteStatusRegister(clearStatusRegister);
				bscMaster->WriteControlRegister(stopTransferControlRegister);
		}

		return 0;
}
