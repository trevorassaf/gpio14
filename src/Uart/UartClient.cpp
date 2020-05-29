#include "Uart/UartClient.h"

#include <cassert>

#include <glog/logging.h>

namespace Uart
{

UartClient::UartClient() : is_initialized_{false} {}

UartClient::UartClient(std::unique_ptr<Utils::Fd> fd)
  : is_initialized_{true},
    fd_{std::move(fd)} {}

UartClient::UartClient(UartClient &&other)
{
  StealResources(&other);
}

UartClient& UartClient::operator=(UartClient &&other)
{
  if (this != &other)
  {
    StealResources(&other);
  }
  return *this;
}

UartClient::~UartClient()
{
  Close();
}

bool UartClient::IsOpen() const
{
  return fd_ != nullptr;
}

void UartClient::Close()
{
  if (!is_initialized_)
  {
    return;
  }

  is_initialized_ = false;
  fd_.reset();
}

bool UartClient::Write(const uint8_t *buffer, size_t size)
{
  assert(is_initialized_);
  assert(buffer);
  assert(IsOpen());

  auto result = fd_->Write(buffer, size);
  if (!result.IsOk())
  {
    LOG(ERROR) << "UART write operation failed. Buffer size: "
               << size;
    return false;
  }

  return true;
}

bool UartClient::Read(uint8_t *buffer, size_t size)
{
  assert(is_initialized_);
  assert(buffer);
  assert(IsOpen());

  auto result = fd_->Read(buffer, size);
  if (!result.IsOk())
  {
    LOG(ERROR) << "UART read operation failed. Buffer size: "
               << size;
    return false;
  }

  return true;
}

void UartClient::StealResources(UartClient *other)
{
  assert(other);
  is_initialized_ = other->is_initialized_;
  other->is_initialized_ = false;
  fd_ = std::move(other->fd_);
}

} // namespace Uart
