#pragma once

#include <cstdlib>

namespace I2c
{
class ControlRegister
{
public:
	ControlRegister(
			bool i2cEnabled,
			bool rxInteruptsEnabled,
			bool txInterruptsEnabled,
			bool doneInteruptsEnabled,
			bool startTransfer,
			bool clearFifo,
			bool readTransfer)
	: m_i2cEnabled{i2cEnabled},
		m_rxInteruptsEnabled{rxInteruptsEnabled},
		m_txInteruptsEnabled{txInteruptsEnabled},
		m_doneInteruptsEnabled{doneInteruptsEnabled},
		m_startTransfer{startTransfer},
		m_clearFifo{clearFifo},
		m_readTransfer{readTransfer}
{}

bool GetI2cEnabled() const { return m_i2cEnabled; }
bool GetRxInteruptsEnabled() const { return m_rxInteruptsEnabled; }
bool GetTxInteruptsEnabled() const { return m_txInteruptsEnabled; }
bool GetDoneInteruptsEnabled() const { return m_doneInteruptsEnabled; }
bool GetStartTransfer() const { return m_startTransfer; }
bool GetClearFifo() const { return m_clearFifo; }
bool GetReadTransfer() const { return m_readTransfer; }

private:
	const bool m_i2cEnabled;
	const bool m_rxInteruptsEnabled;
	const bool m_txInteruptsEnabled;
	const bool m_doneInteruptsEnabled;
	const bool m_startTransfer;
	const bool m_clearFifo;
	const bool m_readTransfer;
};

class ControlRegisterBuilder
{
public:
	ControlRegisterBuilder()
		: m_i2cEnabled{false},
			m_rxInteruptsEnabled{false},
			m_txInteruptsEnabled{false},
			m_doneInteruptsEnabled{false},
			m_startTransfer{false},
			m_clearFifo{false},
			m_readTransfer{false}
	{}

ControlRegisterBuilder &EnableI2c()
{
		m_i2cEnabled = true;
		return *this;
}

ControlRegisterBuilder &EnableRxInterupts()
{
		m_rxInteruptsEnabled = true;
		return *this;
}

ControlRegisterBuilder &EnableTxInterupts()
{
		m_txInteruptsEnabled = true;
		return *this;
}
ControlRegisterBuilder &EnableDoneInterupts()
{
		m_doneInteruptsEnabled = true;
		return *this;
}
ControlRegisterBuilder &StartTransfer()
{
		m_startTransfer = true;
		return *this;
}
ControlRegisterBuilder &ClearFifo()
{
		m_clearFifo = true;
		return *this;
}

ControlRegisterBuilder &ReadTransfer()
{
		m_readTransfer = true;
		return *this;
}

ControlRegister Build() const
{
		return ControlRegister{
				m_i2cEnabled,
				m_rxInteruptsEnabled,
				m_txInteruptsEnabled,
				m_doneInteruptsEnabled,
				m_startTransfer,
				m_clearFifo,
				m_readTransfer};
}

private:
	bool m_i2cEnabled;
	bool m_rxInteruptsEnabled;
	bool m_txInteruptsEnabled;
	bool m_doneInteruptsEnabled;
	bool m_startTransfer;
	bool m_clearFifo;
	bool m_readTransfer;
};

} // namespace I2c
