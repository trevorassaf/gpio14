#pragma once

#include "Pin.h"

namespace gpio {

class InputPin {
 public:
  InputPin(Pin pin);
  ~InputPin();

  const Pin& GetPin() const;

 private:
  Pin pin_;
};

} // namespace gpio
