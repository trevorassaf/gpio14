#pragma once

#include <cstdint>
#include <memory>
#include <string>
#include <utility>

#include "Utils/Fd.h"

namespace Uart
{

class UartClient
{
public:
	UartClient();
	UartClient(std::unique_ptr<Utils::Fd> fd);
	UartClient(UartClient &&other);
	UartClient& operator=(UartClient &&other);
	~UartClient();

	bool IsOpen() const;
	void Close();
	bool Write(const uint8_t *buffer, size_t size);
	bool Read(uint8_t *buffer, size_t size);

private:
  void StealResources(UartClient *other);

private:
	UartClient(const UartClient &other) = delete;
	UartClient& operator=(const UartClient &other) = delete;

private:
  bool is_initialized_;
	std::unique_ptr<Utils::Fd> fd_;
};

} // namespace Uart
