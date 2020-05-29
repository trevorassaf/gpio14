#pragma once

#include <memory>

#include "Uart/UartClient.h"
#include "Uart/UartClientFactory.h"
#include "System/RpiSystemContext.h"

namespace Uart
{
class RpiUartContext
{
public:
	RpiUartContext(System::RpiSystemContext *rpi_context);
	bool GetSerial0(UartClient **out_serial_0);

private:
	bool p_LazyInitializeBus(
      const std::string &device_name,
      std::unique_ptr<UartClient> *out_client);

private:
	System::RpiSystemContext *rpi_context_;
	UartClientFactory client_factory_;
	std::unique_ptr<UartClient> serial_0_;
};
} // namespace Uart
