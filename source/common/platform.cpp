#include "platform.hpp"

using namespace ::hh::common;

using ::std::string;

/// \brief TODOCUMENT
///
/// \relates platform
platform hh::common::get_platform() {
#ifdef  __GNUC__
#ifdef __clang__
	return platform::CLANG;
#endif
#endif
	return platform::GCC;
}

/// \brief TODOCUMENT
///
/// \relates platform
string hh::common::to_string(const platform &arg_platform ///< TODOCUMENT
                             ) {
	switch ( arg_platform ) {
		case ( platform::CLANG ) : { return "Clang"; }
		case ( platform::GCC   ) : { return "GCC"  ; }
	}
	throw "Cannot recognise platform value";
}

/// \brief TODOCUMENT
///
/// \relates platform
string hh::common::get_platform_string() {
	return to_string( get_platform() );
}

