#ifndef SOURCE_COMMON_TUPLE_TUPLE_TO_STRING_JOIN_H
#define SOURCE_COMMON_TUPLE_TUPLE_TO_STRING_JOIN_H

#include <boost/algorithm/string/join.hpp>

#include "common/cpp17/tuple_variable_templates.hpp"
#include "common/tuple/tuple_index_sequence.hpp"

#include <string>
#include <tuple>
#include <type_traits>

namespace hh::common {
	namespace detail {

		/// \brief TODOCUMENT
		template <typename... Strs>
		std::string join_strings(const std::string  &   arg_joinee, ///< TODOCUMENT
		                         Strs              &&...arg_strings ///< TODOCUMENT
		                         ) {
			// Make and then join an initializer_list of the strings.
			// Simple but inefficient.
			const auto strings_il = { arg_strings... };
			return boost::algorithm::join( strings_il, arg_joinee );
		}

		/// \brief Implementation of tuple_add
		template <typename Tpl, size_t... Index>
		std::string tuple_to_string_join_impl(const Tpl         &arg_tuple,  ///< The tuple to to_string and join
		                                      const std::string &arg_joinee, ///< The string to use in the join
		                                      std::index_sequence<Index...>  ///< An index_sequence matching the indices of Tpl
		                                      ) {
			using std::to_string;
			return join_strings( arg_joinee, to_string( std::get<Index>( arg_tuple ) )... );
		}

	} // namespace detail


	/// \brief Return the result of element-wise to_string_joining one tuple to another
	template <typename Tpl>
	std::string tuple_to_string_join(const Tpl         &arg_tuple, ///< The tuple to to_string and join
	                                 const std::string &arg_joinee ///< The string to use in the join
	                                 ) {
		return detail::tuple_to_string_join_impl(
			arg_tuple,
			arg_joinee,
			detail::tuple_index_sequence<Tpl>{}
		);
	}

} // namespace hh::common

#endif
