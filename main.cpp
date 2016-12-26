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
  assert(argc == 3);
  int pin_idx1 = std::stoi(argv[1]);
  int pin_idx2 = std::stoi(argv[2]);

  // Assemble PinFactory
  auto memory_config = std::make_shared<gpio::MemoryConfig>();

  auto manager = std::make_shared<gpio::PinManager>(
      memory_config,
      std::make_unique<gpio::MmioBcm2835MemorySegment>(memory_config));

  auto factory = std::make_unique<gpio::PinFactory>(manager);

  // Configure pin for output
  std::unique_ptr<gpio::OutputPin> pin1 = factory->BindOutputPin(pin_idx1);
  std::unique_ptr<gpio::OutputPin> pin2 = factory->BindOutputPin(pin_idx2);

  std::thread pin1_thread([&] {
    while (true) {
      std::cout << "Setting pin " << pin_idx1 << " high" << std::endl;
      pin1->Set();
      std::cout << "Reading pin " << pin_idx1 << " value: "
                << std::boolalpha << pin1->Read() << std::endl;
      std::this_thread::sleep_for(std::chrono::milliseconds(500));
      std::cout << "Setting pin " << pin_idx1 << " low" << std::endl;
      pin1->Clear();
      std::cout << "Reading pin " << pin_idx1 << " value: "
                << std::boolalpha << pin1->Read() << std::endl;
      std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
  });

  std::this_thread::sleep_for(std::chrono::milliseconds(500));

  std::thread pin2_thread([&] {
    while (true) {
      std::cout << "Setting pin " << pin_idx2 << " high" << std::endl;
      pin2->Set();
      std::cout << "Reading pin " << pin_idx2 << " value: "
                << std::boolalpha << pin2->Read() << std::endl;
      std::this_thread::sleep_for(std::chrono::milliseconds(500));
      std::cout << "Setting pin " << pin_idx2 << " low" << std::endl;
      pin2->Clear();
      std::cout << "Reading pin " << pin_idx2 << " value: "
                << std::boolalpha << pin2->Read() << std::endl;
      std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
  });

  pin1_thread.join();
  pin2_thread.join();
  
  return 0;
}
