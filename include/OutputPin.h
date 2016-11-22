#pragma once

#include "Pin.h"

namespace gpio {

class OutputPin {
 public:
  OutputPin(Pin pin);
  ~OutputPin();

  const Pin& GetPin() const;

 private:
  Pin pin_;
};

} // namespace gpio
