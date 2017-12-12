#include "cont.hpp"

#include <iostream>
#include <iterator>

using ::boost::make_optional;
using ::boost::none;
using ::boost::optional;
using ::std::distance;

using namespace ::hh::part;

/// \brief TODOCUMENT
auto cont::insert(const_iterator  arg_itr, ///< TODOCUMENT
                  const elem     &arg_val  ///< TODOCUMENT
                  ) -> iterator {
	return elements.insert( std::move( arg_itr ), arg_val );
}

/// \brief TODOCUMENT
auto cont::insert(const_iterator   arg_itr, ///< TODOCUMENT
                  elem           &&arg_val  ///< TODOCUMENT
                  ) -> iterator {
	return elements.insert( std::move( arg_itr ), std::move( arg_val ) );
}

/// \brief TODOCUMENT
auto cont::erase(const_iterator arg_itr
                 ) -> iterator {
	return elements.erase( move( arg_itr ) );
}

/// \brief TODOCUMENT
auto cont::begin() const -> const_iterator {
	return std::cbegin( elements );
}

/// \brief TODOCUMENT
auto cont::end() const -> const_iterator {
	return std::cend( elements );
}

/// \brief TODOCUMENT
auto cont::begin() -> iterator {
	return std::begin( elements );
}

/// \brief TODOCUMENT
auto cont::end() -> iterator {
	return std::end( elements );
}

/// \brief TODOCUMENT
optional<size_t> cont::get_index(const elem &arg_elem ///< TODOCUMENT
                                 ) const {
	return ( ! elements.empty() && &arg_elem >= &elements.front() && &arg_elem <= &elements.back() )
		? make_optional( static_cast<size_t>( distance<const elem *>( &elements.front(), &arg_elem ) ) )
		: none;
}

