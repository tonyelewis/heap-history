#ifndef SOURCE_COMMON_CPP17_TUPLE_VARIABLE_TEMPLATES_H
#define SOURCE_COMMON_CPP17_TUPLE_VARIABLE_TEMPLATES_H

#include <tuple>

namespace hh::common {

	/// \brief TODOCUMENT
	template <typename T>
	constexpr std::size_t tuple_size_v = std::tuple_size<T>::value;

} // namespace hh::common

#endif

