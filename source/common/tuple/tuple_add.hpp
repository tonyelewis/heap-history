#ifndef SOURCE_COMMON_TUPLE_TUPLE_ADD_H
#define SOURCE_COMMON_TUPLE_TUPLE_ADD_H

#include "common/cpp17/tuple_variable_templates.hpp"
#include "common/tuple/tuple_index_sequence.hpp"

#include <tuple>
#include <type_traits>

namespace hh::common {
	namespace detail {

		/// \brief Implementation of tuple_add
		template <typename Tpl, size_t... Index>
		constexpr Tpl tuple_add_impl(const Tpl &arg_tuple_a,       ///< The first  tuple to add
		                             const Tpl &arg_tuple_b,       ///< The second tuple to add
		                             std::index_sequence<Index...> ///< An index_sequence matching the indices of Tpl
		                             ) {
			return { ( std::get<Index>( arg_tuple_a ) + std::get<Index>( arg_tuple_b ) )... };
		}

	} // namespace detail


	/// \brief Return the result of element-wise adding one tuple to another
	template <typename Tpl>
	constexpr Tpl tuple_add(const Tpl &arg_tuple_a, ///< The first  tuple to add
	                        const Tpl &arg_tuple_b  ///< The second tuple to add
	                        ) {
		return detail::tuple_add_impl(
			arg_tuple_a,
			arg_tuple_b,
			detail::tuple_index_sequence<Tpl>{}
		);
	}

} // namespace hh::common

#endif
