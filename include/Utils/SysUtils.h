#pragma once

#include <errno.h>

#include <cstring>
#include <string>

namespace Utils {

class SysUtils {
	public:
		static std::string GetErrorMessage() {
			return GetErrorMessage(errno);
		}

		static std::string GetErrorMessage(int error_num) {
			return std::string(strerror_r(error_num, nullptr, 0));
		}
};

} // namespace Utils
