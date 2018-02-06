#pragma once

namespace Utils
{

class FdOpResult
{
public:
	static FdOpResult Ok() { return FdOpResult{false, 0}; }
	static FdOpResult Bad(int errorCode) { return FdOpResult{true, errorCode}; }

	FdOpResult(bool isError, int errorCode) : m_isError{isError}, m_errorCode{errorCode} {}

	bool IsOk() { return !m_isError; }
	int GetErrorCode() { return m_errorCode; }

private:
	bool m_isError;
	int m_errorCode;
};

} // namespace Utils
