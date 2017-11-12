#pragma once

namespace I2c
{
class StatusRegister
{
public:
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
			bool transferActive)
	: m_clockStretchTimeout{clockStretchTimeout},
		m_ackError{ackError},
		m_fifoFull{fifoFull},
		m_fifoEmpty{fifoEmpty},
		m_fifoContainsData{fifoContainsData},
		m_fifoCanAcceptData{fifoCanAcceptData},
		m_fifoNeedsReading{fifoNeedsReading},
		m_fifoNeedsWriting{fifoNeedsWriting},
		m_transferDone{transferDone},
		m_transferActive{transferActive}
	{}

bool IsClockStretchTimeout() const { m_clockStretchTimeout; }
bool IsAckError() const { m_ackError; }
bool IsFifoFull() const { m_fifoFull; }
bool IsFifoEmpty() const { m_fifoEmpty; }
bool IsFifoContainsData() const { m_fifoContainsData; }
bool IsFifoCanAcceptData() const { m_fifoCanAcceptData; }
bool IsFifoNeedsReading() const { m_fifoNeedsReading; }
bool IsFifoNeedsWriting() const { m_fifoNeedsWriting; }
bool IsTransferDone() const { m_transferDone; }
bool IsTransferActive() const { m_transferActive; }

private:
	const bool m_clockStretchTimeout;
	const bool m_ackError;
	const bool m_fifoFull;
	const bool m_fifoEmpty;
	const bool m_fifoContainsData;
	const bool m_fifoCanAcceptData;
	const bool m_fifoNeedsReading;
	const bool m_fifoNeedsWriting;
	const bool m_transferDone;
	const bool m_transferActive;
};

class StatusRegisterBuilder
{
public:
	StatusRegister()
		: m_clockStretchTimeout{false},
			m_ackError{false},
			m_fifoFull{false},
			m_fifoEmpty{false},
			m_fifoContainsData{false},
			m_fifoCanAcceptData{false},
			m_fifoNeedsReading{false},
			m_fifoNeedsWriting{false},
			m_transferDone{false},
			m_transferActive{false}
	{}

StatusRegister &SetClockStretchTimeout(bool value)
{
		m_clockStretchTimeout = value;
		return *this;
}

StatusRegister &SetAckError(bool value)
{
		m_ackError = value;
		return *this;
}

StatusRegister &SetFifoFull(bool value)
{
		m_fifoFull = value;
		return *this;
}

StatusRegister &SetFifoEmpty(bool value)
{
		m_fifoEmpty = value;
		return *this;
}

StatusRegister &SetFifoContainsData(bool value)
{
		m_fifoContainsData = value;
		return *this;
}

StatusRegister &SetFifoCanAcceptData(bool value)
{
		m_fifoCanAcceptData = value;
		return *this;
}

StatusRegister &SetFifoNeedsReading(bool value)
{
		m_fifoNeedsReading = value;
		return *this;
}
StatusRegister &SetFifoNeedsWriting(bool value)
{
		m_fifoNeedsWriting = value;
		return *this;
}
StatusRegister &SetTransferDone(bool value)
{
		m_transferDone = value;
		return *this;
}
StatusRegister &SetTransferActive(bool value)
{
		m_transferActive = value;
		return *this;
}

StatusRegister Build() const
{
		return StatusRegister{
				m_clockStretchTimeout,
				m_ackError,
				m_fifoFull,
				m_fifoEmpty,
				m_fifoContainsData,
				m_fifoCanAcceptData,
				m_fifoNeedsReading,
				m_fifoNeedsWriting,
				m_transferDone,
				m_transferActive};
}

private:
	bool m_clockStretchTimeout;
	bool m_ackError;
	bool m_fifoFull;
	bool m_fifoEmpty;
	bool m_fifoContainsData;
	bool m_fifoCanAcceptData;
	bool m_fifoNeedsReading;
	bool m_fifoNeedsWriting;
	bool m_transferDone;
	bool m_transferActive;
};
} // namespace I2c
