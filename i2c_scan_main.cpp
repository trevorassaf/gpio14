#include <cstdint>

#include "I2c/I2cClientFactory.h"
#include "I2c/I2cClient.h"
#include "Utils/BasicFdOps.h"
#include "Utils/FdOps.h"

using I2c::I2cClient;
using I2c::I2cClientFactory;
using Utils::BasicFdOps;
using Utils::FdOps;

constexpr uint8_t I2C_MAX_ADDRESS = 0x7F;

int main(int argc, const char **argv)
{
		BasicFdOps basicFdOps;
		I2cClientFactory factory{&basicFdOps};
		auto client = factory.Make("/dev/i2c-1");
		return 0;
}
