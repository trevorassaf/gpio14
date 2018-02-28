#pragma once

namespace Utils
{
class IoctlOps
{
public:
	bool SetI2cSlave(int fd, uint8_t slaveAddress);
};
} // namespace Utils
