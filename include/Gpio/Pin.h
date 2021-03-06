#pragma once

#include <cstdint>
#include <memory>

#include "Gpio/PinManager.h"

namespace Gpio {

class Pin {
public:
  Pin();
  Pin(
			PinManager *pinManager,
      uint8_t index);

  // Releases the pin from its registered function.
  ~Pin();
  Pin(Pin &&other);
  Pin &operator=(Pin &&other);

  // Returns the index of this pin.
  uint8_t GetIndex() const;

  // Asserts this pin.
  void Set();

  // Deasserts this pin.
  void Clear();

  // Returns true iff pin is asserted.
  bool Read() const;

private:
  void CloseResources();
  void StealResources(Pin *other);

private:
  Pin(const Pin& other) = delete;
  Pin& operator=(const Pin& other) = delete;

private:
  uint8_t m_index;

  // This pin is bound to the lifetime of the PinManager.
	PinManager *m_pinManager;
};

} // namespace Gpio
