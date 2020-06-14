#include "Uart/UartClientFactory.h"

#include <fcntl.h>
#include <termios.h>

#include <cassert>
#include <memory>
#include <string>
#include <utility>

#include <glog/logging.h>

#include "Uart/UartClient.h"
#include "Utils/Fd.h"
#include "Utils/FdOps.h"
#include "Utils/FdException.h"

namespace
{
using Utils::Fd;
using Utils::FdOps;
using Utils::FdException;
}  // namespace

namespace Uart
{

UartClientFactory::UartClientFactory(FdOps *fd_ops) : fd_ops_{fd_ops} {}

bool UartClientFactory::Make(const std::string &device_name, UartClient *out_client)
{
  assert(out_client);

  std::unique_ptr<Fd> fd;
  try
  {
    fd = std::make_unique<Fd>(
        fd_ops_,
        device_name.c_str());
  }
  catch (const FdException &e)
  {
    LOG(ERROR) << "Failed to open UART device: " << e.what();
    return false;
  }

  if (tcflush(fd->Get(), TCIOFLUSH) < 0)
  {
    LOG(ERROR) << "Failed to tcflush. Non-fatal error: " << strerror(errno);
  }

  struct termios uart_options;
  if (tcgetattr(fd->Get(), &uart_options) < 0)
  {
    LOG(ERROR) << "Failed to call tcgetattr(): " << strerror(errno);
    return false;
  }

  speed_t baud_rate = B1000000;
  cfsetospeed(&uart_options, baud_rate);
  cfsetispeed(&uart_options, baud_rate);

  // 8 bit data
  // one stop bit
  // none parity
  // set raw uart mode

  uart_options.c_cflag &= ~PARENB;
  uart_options.c_cflag &= ~CSTOPB;
  uart_options.c_cflag |= CLOCAL;
  uart_options.c_cflag |= CREAD;
  cfmakeraw(&uart_options);

  if (tcsetattr(fd->Get(), TCSANOW, &uart_options) < 0)
  {
    LOG(ERROR) << "Failed to call tcsetattr(): " << strerror(errno);
    return false;
  }

  *out_client = UartClient{std::move(fd)};
  return true;
}

}  // namespace Uart
