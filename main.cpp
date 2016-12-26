#include "MemoryConfig.h"
#include "MmioBcm2835MemorySegment.h"
#include "MemorySegment.h"
#include "PinManager.h"
#include "PinFactory.h"
#include "OutputPin.h"
#include "ScopeGuard.h"
#include "SysUtils.h"

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

using namespace gpio;

int main(int argc, char** argv) {
  assert(argc == 2);
  int pin_idx = std::stoi(argv[1]);

  // Assemble PinFactory
  auto memory_config = std::make_shared<gpio::MemoryConfig>();

  auto manager = std::make_shared<gpio::PinManager>(
      memory_config,
      std::make_unique<gpio::MmioBcm2835MemorySegment>(memory_config));

  auto factory = std::make_unique<gpio::PinFactory>(manager);

  // Configure pin for output
  std::cout << "Configuring pin " << pin_idx << " for output" << std::endl;
  std::unique_ptr<gpio::OutputPin> pin = factory->BindOutputPin(pin_idx);

  while (true) {
    std::cout << "Setting pin " << pin_idx << " high" << std::endl;
    pin->Set();
    std::cout << "Reading pin " << pin_idx << " value: "
              << std::boolalpha << pin->Read() << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    std::cout << "Setting pin " << pin_idx << " low" << std::endl;
    pin->Clear();
    std::cout << "Reading pin " << pin_idx << " value: "
              << std::boolalpha << pin->Read() << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
  }
  
  return 0;
}
