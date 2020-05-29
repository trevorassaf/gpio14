#include "Uart/RpiUartContext.h"

#include <cassert>

#include <glog/logging.h>

namespace
{
using System::RpiSystemContext;

const std::string SERIAL_0_DEVICE_FILE = "/dev/serial0";
}  // namespace

namespace Uart
{

RpiUartContext::RpiUartContext(System::RpiSystemContext *rpi_context)
  : rpi_context_{rpi_context},
    client_factory_{rpi_context_->GetFdOps()},
    serial_0_{} {}

bool RpiUartContext::GetSerial0(UartClient **out_serial_0)
{
  assert(out_serial_0);

  if (!p_LazyInitializeBus(SERIAL_0_DEVICE_FILE, &serial_0_))
  {
    LOG(ERROR) << "Failed to initialize UART bus: " << SERIAL_0_DEVICE_FILE;
    return false;
  }

  *out_serial_0 = serial_0_.get();
  return true;
}

bool RpiUartContext::p_LazyInitializeBus(
    const std::string &device_name,
    std::unique_ptr<UartClient> *out_client)
{
  assert(out_client);

  if (*out_client == nullptr )
  {
    *out_client = std::make_unique<UartClient>();
    if (!client_factory_.Make(device_name, out_client->get()))
    {
      LOG(ERROR) << "Failed to lazy initialize UART device: " << device_name;
      out_client->reset();
      return false;
    }
  }

  return true;
}

}  // namespace Uart
