#pragma once

#include <stdexcept>
#include <string>

namespace Utils
{
class FdException : public std::runtime_error
{
public:
	FdException(const std::string &what) : std::runtime_error{what} {}
};
} // namespace Utils
