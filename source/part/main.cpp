#include "cont.hpp"
#include "elem.hpp"

#include <iostream>
#include <utility>
#include <algorithm>

using namespace ::hh::part;

using ::std::begin;
using ::std::cbegin;
using ::std::cend;
using ::std::cerr;
using ::std::end;
using ::std::move;
using ::std::sort;
using ::std::swap;

template <typename... Ts> void ignore_unused(Ts...) {}

int main() {
	cont container;
	for (int i = 0; i < 10000; ++i) {
		container.emplace_back( 8.0 );
		container.emplace_back( 2.0 );
		container.emplace_back( 4.0 );
		container.emplace_back( 5.0 );
		container.emplace_back( 3.0 );
		container.emplace_back( 4.0 );
		container.emplace_back( 7.0 );
		container.emplace_back( 1.0 );
		container.emplace_back( 1.0 );
		container.emplace_back( 6.0 );
	}

	std::cerr << "Start std::make_heap()\n";

	std::sort(
		begin( container ),
		end  ( container )
	);

	std::cerr << "Finish std::make_heap()\n";

	container.erase( cbegin( container ) );
}
