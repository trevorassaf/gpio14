cmake_minimum_required(VERSION 3.1)

include_directories(include)

add_library(gpio14 STATIC
  src/I2c/BasicI2cIoctlOps.cpp
  src/I2c/I2cClient.cpp
  src/I2c/I2cClientFactory.cpp
  src/I2c/RpiI2cContext.cpp
  src/Gpio/InputPin.cpp
  src/Gpio/OutputPin.cpp
  src/Gpio/Pin.cpp
  src/Gpio/PinFactory.cpp
  src/Gpio/PinManager.cpp
  src/Gpio/PinType.cpp
  src/Gpio/RpiPinManager.cpp
  src/I2c/Devices/Ads1115AnalogToDigitalConverter/Ads1115.cpp
  src/Memory/MmioBcm2835MemorySegment.cpp
  src/Memory/MmioConfig.cpp
  src/System/RpiSystemContext.cpp
  src/Uart/RpiUartContext.cpp
  src/Uart/UartClient.cpp
  src/Uart/UartClientFactory.cpp
  src/Utils/BasicFdOps.cpp
  src/Utils/Fd.cpp)

target_link_libraries(gpio14 glog::glog)

