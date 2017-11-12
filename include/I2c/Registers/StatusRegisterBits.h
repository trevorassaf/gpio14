#pragma once

#include <cstdlib>

namespace I2c
{
class StatusRegisterBits
{
public:
	size_t GetClockStretchOffset() const;
	size_t GetAckErrorOffset() const;
	size_t GetFifoFullOffset() const;
	size_t GetFifoEmptyOffset() const;
	size_t GetFifoContainsDataOffset() const;
	size_t GetFifoCanAcceptDataOffset() const;
	size_t GetFifoNeedsReadingOffset() const;
	size_t GetFifoNeedsWritingOffset() const;
	size_t GetTransferDoneOffset() const;
	size_t GetTransferActiveOffset() const;
};
} // namespace I2c
