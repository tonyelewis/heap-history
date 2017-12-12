#include "elem.hpp"

#include <boost/optional/optional_io.hpp>

#include "part/cont.hpp"

#include <iostream>
#include <algorithm>

using ::boost::optional;
using ::std::move;
using ::std::cerr;

using namespace ::hh::part;
using namespace ::hh::part::detail;

/// \brief TODOCUMENT
elem::elem(silent_construct_tag, ///< TODOCUMENT
           elem                 &&arg_elem ///< TODOCUMENT
           ) : parent{ arg_elem.parent        },
               value { move( arg_elem.value ) } {
}

/// \brief TODOCUMENT
elem & elem::silent_move_assign(elem &&arg_elem ///< TODOCUMENT
                                ) {
	parent = move( arg_elem.parent );
	value  = move( arg_elem.value  );
	return *this;
}

/// \brief TODOCUMENT
elem::elem(const cont &arg_parent ///< TODOCUMENT
           ) : parent { arg_parent } {
	cerr << "Default ctor\n";
}

/// \brief TODOCUMENT
elem::elem(const cont &arg_parent, ///< TODOCUMENT
           double      arg_value
           ) : parent { arg_parent        },
               value  { move( arg_value ) } {
	cerr << "Ctor " << get_index() << "\n";
}

/// \brief TODOCUMENT
elem::elem(const elem &arg_elem ///< TODOCUMENT
           ) : parent{ arg_elem.parent },
               value { arg_elem.value  } {
	cerr << "Copy ctor\n";
}

/// \brief TODOCUMENT
elem::elem(elem &&arg_elem ///< TODOCUMENT
           ) : parent{ arg_elem.parent        },
               value { move( arg_elem.value ) } {
	cerr << "Move ctor from " << arg_elem.get_index() << " to " << get_index() << "\n";
}

/// \brief TODOCUMENT
elem::~elem() {
	try {
		if ( volume == detail::dtor_volume::NOISY ) {
			cerr << "Dtor " << get_index() << "\n";
		}
	}
	catch (...) {}
}

/// \brief TODOCUMENT
elem & elem::silence() {
	volume = detail::dtor_volume::SILENT;
	return *this;
}

/// \brief TODOCUMENT
elem & elem::operator=(const elem &arg_elem ///< TODOCUMENT
                       ) {
	cerr << "Copy assign from " << arg_elem.get_index() << " to " << get_index() << "\n";
	parent = arg_elem.parent;
	value  = arg_elem.value;
	return *this;
}

/// \brief TODOCUMENT
elem & elem::operator=(elem &&arg_elem ///< TODOCUMENT
                       ) {
	cerr << "Move assign from " << arg_elem.get_index() << " to " << get_index() << "\n";
	parent = move( arg_elem.parent );
	value  = move( arg_elem.value  );
	return *this;
}

/// \brief TODOCUMENT
const double & elem::get_value() const {
	return value;
}

/// \brief TODOCUMENT
optional<size_t> elem::get_index() const {
	return parent.get().get_index( *this );
}

/// \brief TODOCUMENT
bool hh::part::operator<(const elem &arg_lhs, ///< TODOCUMENT
                         const elem &arg_rhs  ///< TODOCUMENT
                         ) {
	cerr << "Less between " << arg_lhs.get_index() << " and " << arg_rhs.get_index() << "\n";
	return ( arg_lhs.get_value() < arg_rhs.get_value() );
}

/// \brief TODOCUMENT
void hh::part::swap(elem &arg_lhs, ///< TODOCUMENT
                    elem &arg_rhs  ///< TODOCUMENT
                    ) {
	if ( &arg_lhs != &arg_rhs ) {
		std::cerr << "Swap between " << arg_lhs.get_index() << " and " << arg_rhs.get_index() << "\n";
		elem temp{ silent_construct_tag{}, move( arg_rhs ) };
		arg_rhs.silent_move_assign( move( arg_lhs ) );
		arg_lhs.silent_move_assign( move( temp    ) );
		temp.silence();
	}
	else {
		std::cerr << "Self-swap!\n";
	}
}
