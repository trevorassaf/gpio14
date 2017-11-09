#pragma once

#include <errno.h>

#include <cstring>
#include <string>
#include <memory>
#include <utility>

namespace Utility {

class SysUtils {
	public:
		static std::unique_ptr<char[]> GetBuffer(size_t size) {
			return std::make_unique<char[]>(size);
		}

		static std::string GetErrorMessage() {
			return GetErrorMessage(errno);
		}

		static std::string GetErrorMessage(int error_num) {
			// Initialize and clear buffer
			std::unique_ptr<char[]> buffer = GetBuffer(ERROR_STRING_BUFFER_SIZE+1);
			std::memset(
					static_cast<void*>(buffer.get()),
					0,
					ERROR_STRING_BUFFER_SIZE+1);

			// Obtain error string
			strerror_r(error_num, buffer.get(), ERROR_STRING_BUFFER_SIZE);
			return std::string(buffer.get(), ERROR_STRING_BUFFER_SIZE);
		}

	private:
		static constexpr size_t ERROR_STRING_BUFFER_SIZE = 256;
};

} // namespace Utility
