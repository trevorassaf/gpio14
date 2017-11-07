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

int main(int argc, char** argv) {
  // Assemble PinFactory
	auto memoryConfig = std::unique_ptr<gpio::MemoryConfig>();

  auto pinManager = std::make_unique<gpio::PinManager>(
      memoryConfig.get(),
      std::make_unique<gpio::MmioBcm2835MemorySegment>(memoryConfig.get()));

  auto factory = std::make_unique<gpio::PinFactory>(pinManager.get());

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

  auto pins = std::make_unique<std::unique_ptr<gpio::OutputPin>[]>(pin_ids.size());
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
