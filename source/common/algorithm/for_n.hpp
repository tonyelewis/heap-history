#ifndef SOURCE_COMMON_ALGORITHM_FOR_N_H
#define SOURCE_COMMON_ALGORITHM_FOR_N_H

#include <boost/core/ignore_unused.hpp>
#include <boost/range/irange.hpp>

#include "common/size_t_literal.hpp"

#include <cstddef>
#include <functional>

namespace hh::common {

	/// \brief Invoke the specified callable the specified number of times
	template <typename Fn>
	void for_n(const size_t  &arg_n, ///< The number of time to invoke the callable
	           Fn           &&arg_fn ///< The callable to invoke the specified number of times
	           ) {
		for (const auto &x : boost::irange( 0_z, arg_n ) ) {
			boost::ignore_unused( x );
			std::invoke( std::forward<Fn>( arg_fn ) );
		}
	}

} // namespace hh::common

#endif
