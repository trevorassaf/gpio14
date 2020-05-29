#pragma once

#include <string>

#include "Uart/UartClient.h"
#include "Utils/Fd.h"
#include "Utils/FdOps.h"

namespace Uart
{

class UartClientFactory
{
public:
  UartClientFactory(Utils::FdOps *fd_ops);
	bool Make(const std::string &deviceName, UartClient *out_client);

private:
  Utils::FdOps *fd_ops_;
};

} // namespace Uart
