#include "Uart/UartClientFactory.h"

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

  *out_client = UartClient{std::move(fd)};
  return true;
}

}  // namespace Uart
