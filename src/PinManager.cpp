#include "PinManager.h"

#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <iostream>
#include <cassert>
#include <bitset>
#include <cstring>
#include <stdexcept>
#include <type_traits>
#include <utility>

#include "SysUtils.h"
#include "ScopeGuard.h"

namespace gpio {

PinManager::PinManager(
		const MemoryConfig *memoryConfig,
    std::unique_ptr<MemorySegment> memorySegment
) : m_memoryConfig{memoryConfig},
    m_memorySegment{std::move(memorySegment)} {
  // Initialize memory locks for binding pin functions. R^W memory regions do not require
  // locks so long as access is volatile qualified.
  InitSelectPinFunctionMutexes();
}

void PinManager::BindPin(uint8_t pinIndex, PinType pinType) {
  // Start critical section for caching pin type
  std::lock_guard<std::mutex> cachePinTypeCriticalSection(m_pinTypeMapMutex);
  assert(m_pinTypeMap.count(pinIndex) == 0);
  m_pinTypeMap[pinIndex] = pinType;

  // Start critical section for informing hw of new pin function
  size_t registerOffset = GetSelectPinFunctionRegisterOffset(pinIndex);
  size_t mutexRegisterOffset = registerOffset * SELECT_PIN_FUNCTION_BYTES_PER_MUTEX;

  assert(m_memoryMutexMap.count(mutexRegisterOffset) == 1);
  std::lock_guard<std::mutex> hwBindPinFunctionCriticalSection(
      m_memoryMutexMap[mutexRegisterOffset]);

  // First, read existing select pin code into temporary. Next, clear current function
  // for desired pin. Then, set new function for desired pin. Finally, write code back
  // to register.
  size_t bitOffset = GetSelectPinFunctionBitOffset(pinIndex);
  volatile uint32_t *gpioMemory =
      (volatile uint32_t *)m_memorySegment->Get();

  uint32_t selectPinFunctionCodes = gpioMemory[registerOffset];
  selectPinFunctionCodes &= ~(0b111 << bitOffset);
  selectPinFunctionCodes |= static_cast<uint32_t>(pinType) << bitOffset;
  gpioMemory[registerOffset] = selectPinFunctionCodes;
}

void PinManager::ReleasePin(uint8_t pinIndex) {
  std::lock_guard<std::mutex> unset_pinType_critical_section(m_pinTypeMapMutex);
  assert(m_pinTypeMap.count(pinIndex) == 1);
  m_pinTypeMap.erase(pinIndex);
}

void PinManager::SetPin(uint8_t pinIndex) {
  SetBit(pinIndex, m_memoryConfig->GetSetPinByteOffset());
}

void PinManager::ClearPin(uint8_t pinIndex) {
  SetBit(pinIndex, m_memoryConfig->GetClearPinByteOffset());
}

bool PinManager::ReadPin(uint8_t pinIndex) {
  return ReadBit(pinIndex, m_memoryConfig->GetReadPinLevelByteOffset());
}

void PinManager::SetBit(uint8_t pinIndex, size_t baseByteOffset) {
  size_t byteOffset = CalculateByteOffset(pinIndex, baseByteOffset);
  volatile uint32_t *setPinPtr =
      (volatile uint32_t *)m_memorySegment->Get() + byteOffset;
  *setPinPtr = (0b1 << (pinIndex % 32));
}

bool PinManager::ReadBit(uint8_t pinIndex, size_t baseByteOffset) {
  size_t byteOffset = CalculateByteOffset(pinIndex, baseByteOffset);
  volatile uint32_t *readPinPtr =
      (volatile uint32_t *)m_memorySegment->Get() + byteOffset;
  return *readPinPtr & (0b1 << (pinIndex % 32));
}

size_t PinManager::GetSelectPinFunctionRegisterOffset(uint8_t pinIndex) const {
  return pinIndex / CODES_PER_SELECT_PIN_FUNCTION_REGISTER;
}

size_t PinManager::GetSelectPinFunctionBitOffset(uint8_t pinIndex) const {
  return (pinIndex % CODES_PER_SELECT_PIN_FUNCTION_REGISTER) * BITS_PER_SELECT_PIN_FUNCTION_CODE;
}

void PinManager::InitMutexes(
  size_t leadingByteOffset,
  size_t bytesPerMutex,
  size_t numMutexes
) {
  size_t limit = leadingByteOffset + bytesPerMutex * numMutexes;
  for (size_t i = leadingByteOffset; i < limit; i += bytesPerMutex) {
    assert(m_memoryMutexMap.count(i) == 0); 
    m_memoryMutexMap[i];
  }
}

void PinManager::InitSelectPinFunctionMutexes() {
  InitMutexes(
      m_memoryConfig->GetSelectPinFunctionByteOffset(),
      SELECT_PIN_FUNCTION_BYTES_PER_MUTEX,
      SELECT_PIN_FUNCTION_MUTEX_COUNT);
}

void PinManager::InitPinFunctionMutexes(size_t leadingByteOffset) {
  InitMutexes(
      leadingByteOffset,
      PIN_FUNCTION_BYTES_PER_MUTEX,
      PIN_FUNCTION_MUTEX_COUNT);
}

size_t PinManager::CalculateByteOffset(uint8_t pinIndex, size_t baseByteOffset) const {
  return (baseByteOffset / 4) + (pinIndex / 32);
}

} // namespace gpio
