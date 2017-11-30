#pragma once

#include <bitset>
#include <sstream>

#include "I2c/Registers/MmioRegister.h"

namespace I2c
{
class ControlRegister : public MmioRegister
{
public:
	static constexpr size_t NUM_BITS = 7;

public:
	ControlRegister();

	ControlRegister(std::bitset<NUM_BITS> bits);

	ControlRegister(
			bool i2cEnabled,
			bool rxInteruptsEnabled,
			bool txInterruptsEnabled,
			bool doneInteruptsEnabled,
			bool startTransfer,
			bool clearFifo,
			bool readTransfer);

	bool IsI2cEnabled() const;
	bool IsRxInteruptsEnabled() const;
	bool IsTxInteruptsEnabled() const;
	bool IsDoneInteruptsEnabled() const;
	bool IsStartTransfer() const;
	bool IsClearFifo() const;
	bool IsReadTransfer() const;

	uint32_t ToMmioRegister() const override;

private:
	const std::bitset<NUM_BITS> m_bits;
};

std::ostream& operator<<(std::ostream &stream, const ControlRegister &reg);

class ControlRegisterBuilder
{
public:
	ControlRegisterBuilder();

	ControlRegisterBuilder &SetI2cEnabled(bool value);
	ControlRegisterBuilder &SetRxInteruptsEnabled(bool value);
	ControlRegisterBuilder &SetTxInteruptsEnabled(bool value);
	ControlRegisterBuilder &SetDoneInteruptsEnabled(bool value);
	ControlRegisterBuilder &SetStartTransfer(bool value);
	ControlRegisterBuilder &SetClearFifo(bool value);
	ControlRegisterBuilder &SetReadTransfer(bool value);

	ControlRegisterBuilder &FromMmioRegister(uint32_t bits);

	ControlRegister Build() const;

private:
	std::bitset<ControlRegister::NUM_BITS> m_bits;
};

} // namespace I2c
