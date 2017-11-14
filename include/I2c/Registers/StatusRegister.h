#pragma once

#include <bitset>
#include <cstdlib>

namespace I2c
{
class StatusRegister
{
public:
	static constexpr size_t NUM_BITS = 10;

public:
	StatusRegister();

	StatusRegister(std::bitset<NUM_BITS> bits);

	StatusRegister(
			bool clockStretchTimeout,
			bool ackError,
			bool fifoFull,
			bool fifoEmpty,
			bool fifoContainsData,
			bool fifoCanAcceptData,
			bool fifoNeedsReading,
			bool fifoNeedsWriting,
			bool transferDone,
			bool transferActive);

	bool IsClockStretchTimeout() const;
	bool IsAckError() const;
	bool IsFifoFull() const;
	bool IsFifoEmpty() const;
	bool IsFifoContainsData() const;
	bool IsFifoCanAcceptData() const;
	bool IsFifoNeedsReading() const;
	bool IsFifoNeedsWriting() const;
	bool IsTransferDone() const;
	bool IsTransferActive() const;

private:
	const std::bitset<NUM_BITS> m_bits;
};

class StatusRegisterBuilder
{
public:
	StatusRegisterBuilder();

	StatusRegisterBuilder &SetClockStretchTimeout(bool value);
	StatusRegisterBuilder &SetAckError(bool value);
	StatusRegisterBuilder &SetFifoFull(bool value);
	StatusRegisterBuilder &SetFifoEmpty(bool value);
	StatusRegisterBuilder &SetFifoContainsData(bool value);
	StatusRegisterBuilder &SetFifoCanAcceptData(bool value);
	StatusRegisterBuilder &SetFifoNeedsReading(bool value);
	StatusRegisterBuilder &SetFifoNeedsWriting(bool value);
	StatusRegisterBuilder &SetTransferDone(bool value);
	StatusRegisterBuilder &SetTransferActive(bool value);

	StatusRegister Build() const;

private:
	std::bitset<StatusRegister::NUM_BITS> m_bits;
};
} // namespace I2c
