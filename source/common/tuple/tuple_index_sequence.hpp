#ifndef SOURCE_COMMON_TUPLE_TUPLE_INDEX_SEQUENCE_H
#define SOURCE_COMMON_TUPLE_TUPLE_INDEX_SEQUENCE_H

#include "common/cpp17/tuple_variable_templates.hpp"

#include <tuple>
#include <type_traits>

namespace hh::common {
	namespace detail {

		/// \brief Helper to get an index_sequence corresponding to the indices of a tuple type
		template <typename Tpl>
		using tuple_index_sequence = std::make_index_sequence< ::hh::common::tuple_size_v< std::decay_t< Tpl > > >;

	} // namespace detail
} // namespace hh::common

#endif
