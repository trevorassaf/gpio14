#include "Gpio/PinType.h"

#include <cstdlib>
#include <string>

#include "glog/logging.h"

namespace Gpio {

const char *ToString(PinType type)
{
  switch (type)
  {
    case PinType::INPUT:
      return "INPUT";
    case PinType::OUTPUT:
      return "OUTPUT";
    case PinType::ALT_0:
      return "ALT_0";
    case PinType::ALT_1:
      return "ALT_1";
    case PinType::ALT_2:
      return "ALT_2";
    case PinType::ALT_3:
      return "ALT_3";
    case PinType::ALT_4:
      return "ALT_4";
    case PinType::ALT_5:
      return "ALT_5";
    default:
      LOG(ERROR) << "Invalid GPIO pin type: " << static_cast<int>(type);
      return "ERROR: INVALID GPIO PIN TYPE";
  }
}
}  // namespace Gpio
