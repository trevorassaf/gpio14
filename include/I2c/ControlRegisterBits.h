#pragma once

#include <cstdlib>

namespace I2c
{

class ControlRegisterBits
{
public:
	enum ClearFifo : int
	{
			NO_ACTION	= 0x00,
			CLEAR_FIFO = 0x01,
	};

public:
	size_t GetI2cEnableOffset() const;
	size_t GetRxIntrOffset() const;
	size_t GetTxIntrOffset() const;
	size_t GetDoneIntrOffset() const;
	size_t GetStartTransferOffset() const;
	size_t GetClearFifoOffset() const;
	size_t GetReadTransferOffset() const;
};
} // namespace I2c
