#ifndef SOURCE_COMMON_SIZE_T_LITERAL_H
#define SOURCE_COMMON_SIZE_T_LITERAL_H

#include <cstddef>

namespace hh::common {
	inline namespace literals {

		/// \brief TODOCUMENT
		constexpr std::size_t operator "" _z ( unsigned long long n ) { return static_cast<size_t>( n ); }

	} // namespace literals
} // namespace hh::common

#endif
