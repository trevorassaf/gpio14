#pragma once

#include <stdexcept>

namespace I2c
{
class I2cException : public std::runtime_error
{
public:
	I2cException(const std::string &what) : std::runtime_error{what} {}
};
} // namespace I2c
