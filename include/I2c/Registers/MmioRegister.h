#pragma once

class MmioRegister
{
public:
	virtual uint32_t ToMmioRegister() const = 0;
};
