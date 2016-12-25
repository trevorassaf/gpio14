#include "MemoryConfig.h"
#include "MmioBcm2835MemorySegment.h"
#include "MemorySegment.h"
#include "PinManager.h"
#include "PinFactory.h"
#include "OutputPin.h"

#include <iostream>
#include <memory>
#include <utility>
#include <thread>
#include <chrono>

int main(int argc, char** argv) {
  // Assemble PinFactory
  auto memory_config = std::make_shared<gpio::MemoryConfig>();

  auto manager = std::make_shared<gpio::PinManager>(
      memory_config,
      std::make_unique<gpio::MmioBcm2835MemorySegment>(memory_config));

  auto factory = std::make_unique<gpio::PinFactory>(manager);

  // Configure BCM pin #20 for output
  gpio::OutputPin pin_20 = factory->BindOutputPin(20);

  while (true) {
    std::cout << "Setting pin 20 high" << std::endl;
    pin_20.Set();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    std::cout << "Setting pin 20 low" << std::endl;
    pin_20.Clear();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
  }

  return 0;
}
