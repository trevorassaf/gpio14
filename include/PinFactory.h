#pragma once

#include <memory>

#include "PinManager.h"

namespace gpio {

class PinFactory {
 public:
  PinFactory(std::unique_ptr<PinManager> pin_manager);

 private:
  std::unique_ptr<PinManager> pin_manager_;
};

} // namespcae gpio
