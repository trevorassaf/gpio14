#include "I2c/Registers/ControlRegister.h"
#include "I2c/Registers/StatusRegister.h"
#include "Gpio/MemoryConfig.h"
#include "Gpio/OutputPin.h"
#include "Gpio/PinManager.h"
#include "Gpio/PinFactory.h"
#include "Memory/MmioBcm2835MemorySegment.h"
#include "Memory/MemorySegment.h"

#include <iostream>
#include <memory>
#include <utility>
#include <thread>
#include <chrono>
#include <utility>
#include <stdexcept>
#include <bitset>
#include <cassert>
#include <string>

#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

using I2c::ControlRegister;
using I2c::StatusRegister;
using Gpio::InputPin;
using Gpio::MemoryConfig;
using Gpio::OutputPin;
using Gpio::PinFactory;
using Gpio::PinManager;
using Memory::MemorySegment;
using Memory::MmioConfig;
using Memory::MmioBcm2835MemorySegment;

int main(int argc, char** argv) {

	ControlRegister controlRegister;
	std::cout << "Control register: \\" << std::endl << controlRegister << std::endl;

	StatusRegister statusRegister;
	std::cout << "StatusRegister: \\" << std::endl << statusRegister << std::endl;

	std::cout << "Shutting down!" << std::endl;
	exit(1);

  // Assemble PinFactory
	MmioConfig gpioMmioConfig = MmioConfig::MakeGpioConfig();
	MemoryConfig gpioMemoryConfig;

	PinManager pinManager{
			&gpioMmioConfig,
      &gpioMemoryConfig,
      std::make_unique<MmioBcm2835MemorySegment>(&gpioMmioConfig)};

  auto factory = std::make_unique<PinFactory>(&pinManager);

  // Declare pin ids
  std::vector<int> pin_ids = {
			14,
			15,
			18,
			23,
			24,
			25,
			8,
			7,
			1,
			12,
			16,
			20,
			21
  };

  auto pins = std::make_unique<std::unique_ptr<Gpio::OutputPin>[]>(pin_ids.size());
  auto threads = std::make_unique<std::unique_ptr<std::thread>[]>(pin_ids.size());

  // Configure pin for output
  for (int i = 0; i < pin_ids.size(); ++i) {
    pins[i] = factory->BindOutputPin(pin_ids[i]);
    threads[i] = std::make_unique<std::thread>([&, i] () -> void {
      std::this_thread::sleep_for(std::chrono::milliseconds(i * 50));
      while (true) {
        pins[i]->Set();
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        pins[i]->Clear();
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
      }
    });
  }

  for (int i = 0; i < pin_ids.size(); ++i) {
    threads[i]->join();
  }

  return 0;
}
