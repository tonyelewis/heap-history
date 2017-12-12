#ifndef SOURCE_COMMON_PLATFORM_H
#define SOURCE_COMMON_PLATFORM_H

#include <string>

namespace hh::common {

	/// \brief TODOCUMENT
	enum class platform : bool {
		CLANG, ///< TODOCUMENT
		GCC    ///< TODOCUMENT
	};

	platform get_platform();

	std::string to_string(const platform &);

	std::string get_platform_string();

} // namespace hh::common

#endif
