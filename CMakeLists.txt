cmake_minimum_required(VERSION 3.1)

include_directories(include)

#target_link_libraries(test_crypto_client test_proto)

add_library(gpio14
  src/I2c/BasicI2cIoctlOps.cpp
  src/I2c/I2cClient.cpp
  src/I2c/I2cClientFactory.cpp
  src/I2c/RpiI2cContext.cpp
  src/I2c/Devices/Ads1115AnalogToDigitalConverter/Ads1115.cpp
  src/Utils/BasicFdOps.cpp
  src/Utils/Fd.cpp
  src/System/RpiSystemContext.cpp)

target_link_libraries(gpio14 glog::glog)
