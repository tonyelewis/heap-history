#ifndef SOURCE_COMMON_TUPLE_TUPLE_SCALAR_DIVIDE_H
#define SOURCE_COMMON_TUPLE_TUPLE_SCALAR_DIVIDE_H

#include "common/cpp17/tuple_variable_templates.hpp"
#include "common/tuple/tuple_index_sequence.hpp"

#include <tuple>
#include <type_traits>

namespace hh::common {
	namespace detail {

		/// \brief Implementation of tuple_scalar_divide
		template <typename Tpl, typename T, size_t... Index>
		constexpr Tpl tuple_scalar_divide_impl(const Tpl &arg_tuple,         ///< The first  tuple to scalar_divide
		                                       const T   &arg_value,         ///< The second tuple to scalar_divide
		                                       std::index_sequence<Index...> ///< An index_sequence matching the indices of Tpl
		                                       ) {
			return { ( std::get<Index>( arg_tuple ) / arg_value )... };
		}

	} // namespace detail

	/// \brief Return the result of element-wise scalar_divideing one tuple to another
	template <typename Tpl, typename T>
	constexpr Tpl tuple_scalar_divide(const Tpl &arg_tuple, ///< The first  tuple to scalar_divide
	                                  const T   &arg_value  ///< The second tuple to scalar_divide
	                                  ) {
		return detail::tuple_scalar_divide_impl(
			arg_tuple,
			arg_value,
			detail::tuple_index_sequence<Tpl>{}
		);
	}

} // namespace hh::common

#endif
