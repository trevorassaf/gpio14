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

#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

using namespace gpio;

int main(int argc, char** argv) {
  /*
  // Assemble PinFactory
  auto memory_config = std::make_shared<gpio::MemoryConfig>();

  auto manager = std::make_shared<gpio::PinManager>(
      memory_config,
      std::make_unique<gpio::MmioBcm2835MemorySegment>(memory_config));

  auto factory = std::make_unique<gpio::PinFactory>(manager);

  // Configure BCM pin #40 for output
  std::cout << "Configuring pin 40 for output" << std::endl;
  std::unique_ptr<gpio::OutputPin> pin_40 = factory->BindOutputPin(40);

  while (true) {
    std::cout << "Setting pin 40 high" << std::endl;
    pin_40->Set();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    std::cout << "Setting pin 40 low" << std::endl;
    pin_40->Clear();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
  }
  */

  // Initialize memory mapped gpio segment
  int fd = open("/dev/mem", O_RDWR | O_SYNC);

  if (fd == -1) {
    throw std::runtime_error(SysUtils::GetErrorMessage());
  }

  ScopeGuard<int> close_file_guard(fd, [] (int& fd) { close(fd); });

  void* memory = mmap(
      nullptr,
      4096,
      PROT_READ | PROT_WRITE,
      MAP_SHARED,
      fd,
      0x3F200000);

  // Handle error
  if (memory == MAP_FAILED) {
    throw std::runtime_error(SysUtils::GetErrorMessage());
  }

  volatile uint32_t* memory_segment_ptr_ = static_cast<volatile uint32_t*>(memory);

  // Configure pin 20 for output
  size_t pin = 4;

  size_t pin_mode_reg = (pin * 3) / 32;
  uint32_t reg = memory_segment_ptr_[pin_mode_reg];
  
  std::cout << "Pin Mode Register Offset: " << pin_mode_reg << std::endl;
  std::cout << "Pin Mode Register Before Mode Switch: "
      << std::bitset<32>(reg) << std::endl;

  size_t pin_mode_shift_idx = (pin * 3) % 32;

  std::cout << "Pin Mode Bit Shift Idx: " << pin_mode_shift_idx << std::endl;

  reg &= ~(0b111 << pin_mode_shift_idx);
  std::cout << "Pin Mode Register After Mode Clear: "
      << std::bitset<32>(reg) << std::endl;

  reg |= 0b001 << pin_mode_shift_idx;
  memory_segment_ptr_[pin_mode_reg] = reg;
  std::cout << "Pin Mode Register After Mode Update: "
      << std::bitset<32>(reg) << std::endl;

  // Blink pin 20
  volatile uint32_t *set_pin_ptr = memory_segment_ptr_ + 0x1C + pin / 32;
  volatile uint32_t *clear_pin_ptr = memory_segment_ptr_ + 0x28 + pin / 32;
  size_t pin_value_shift_idx = pin % 32;
  std::cout << "Pin Value Shift Idx: " << pin_value_shift_idx << std::endl;

  while (true) {
    // Set pin
    std::cout << "Setting pin " << pin << std::endl; 
    *set_pin_ptr |= 0b1 << pin_value_shift_idx;
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    // Clear pin
    std::cout << "Clearing pin " << pin << std::endl; 
    *clear_pin_ptr |= 0b1 << pin_value_shift_idx;
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
  }

  return 0;
}
