#include <boost/algorithm/string/case_conv.hpp>
#include <boost/algorithm/string/join.hpp>
#include <boost/range/adaptor/transformed.hpp>
#include <boost/range/irange.hpp>

#include "common/algorithm/for_n.hpp"
#include "common/platform.hpp"
#include "common/size_t_literal.hpp"
#include "common/tuple/tuple_add.hpp"
#include "common/tuple/tuple_scalar_divide.hpp"
#include "common/tuple/tuple_to_string_join.hpp"

#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <queue>
#include <random>
#include <stdexcept>
#include <tuple>
#include <type_traits>

using namespace ::hh::common;
using namespace ::std::literals::string_literals;

using ::boost::adaptors::transformed;
using ::boost::algorithm::join;
using ::boost::algorithm::to_lower_copy;
using ::boost::irange;
using ::std::chrono::duration;
using ::std::chrono::duration_cast;
using ::std::chrono::seconds;
using ::std::chrono::steady_clock;
using ::std::cout;
using ::std::exception;
using ::std::invoke;
using ::std::make_tuple;
using ::std::mt19937;
using ::std::ofstream;
using ::std::out_of_range;
using ::std::priority_queue;
using ::std::random_device;
using ::std::rotate;
using ::std::string;
using ::std::swap;
using ::std::tuple;
using ::std::uniform_real_distribution;
using ::std::vector;

/// \brief TODOCUMENT
using str_vec  = vector<std::string>;

/// \brief TODOCUMENT
using doub_vec = vector<double>;

/// \brief TODOCUMENT
template <typename Fn, typename... Fns>
auto get_tuple_of_results(Fn  &&   arg_gen_fn, ///< TODOCUMENT
                          Fns &&...arg_fns     ///< TODOCUMENT
                          ) {
	const auto input{ invoke( arg_gen_fn ) };
	return make_tuple( invoke( arg_fns, input )... );
}

/// \brief TODOCUMENT
template <typename Fn, typename... Fns>
auto average_results_over(const size_t  &   arg_num_repeats, ///< TODOCUMENT
                          Fn           &&   arg_gen_fn,      ///< TODOCUMENT
                          Fns          &&...arg_fns          ///< TODOCUMENT
                          ) {
	if ( arg_num_repeats < 1 ) {
		throw out_of_range( "Cannot average over zero repeats" );
	}
	auto result{ get_tuple_of_results( arg_gen_fn, arg_fns... ) };

	for_n(
		arg_num_repeats - 1,
		[&] {
			const auto new_value = get_tuple_of_results( arg_gen_fn, arg_fns... );
			result = tuple_add( result, new_value );
		}
	);

	return tuple_scalar_divide( result, static_cast<double>( arg_num_repeats ) );
}

/// \brief TODOCUMENT
inline doub_vec generate_data(mt19937      &arg_rng, ///< TODOCUMENT
                              const size_t &arg_size ///< TODOCUMENT
                              ) {
	uniform_real_distribution<> dis( 0.0, 100.0 );
	doub_vec data;
	data.reserve( arg_size );
	for_n( arg_size, [&] { data.push_back( dis( arg_rng ) ); } );
	return data;
}

/// \brief TODOCUMENT
doub_vec push_pop_answer(doub_vec arg_data, ///< TODOCUMENT
                         doub_vec new_nums  ///< TODOCUMENT
                         ) {
	for (double &new_num : new_nums) {
		const auto max_itr = max_element( begin( arg_data ), end( arg_data) );
		swap( *max_itr, new_num );
	}
	return new_nums;
}

/// \brief TODOCUMENT
template <typename StrmblRng>
void write_streamables_range_to_file(const string    &arg_filename,   ///< TODOCUMENT
                                     const StrmblRng &arg_streamables ///< TODOCUMENT
                                     ) {
	ofstream out_fstream;
	out_fstream.exceptions( std::ios::failbit | std::ios::badbit );
	try {
		out_fstream.open( arg_filename.c_str() );
	}
	catch (const exception &ex) {
		const string error_message(
			"Cannot open file \""
			+ arg_filename
			+ "\" for writing ["
			+ ex.what()
			+ "] "
		);
		perror( error_message.c_str() );
		throw error_message;
	};

	assert( out_fstream.is_open() );
	assert( out_fstream.good()    );

	for (const auto &x : arg_streamables) {
		out_fstream << x;
	}
	out_fstream.close();
}

int main() {
	random_device rd;
	mt19937 gen{ rd() };

	try {

		if ( false ) {

			write_streamables_range_to_file(
				"graphs/make_heap__vs__sort.data." + to_lower_copy( get_platform_string() ),
				irange( 1000_z, 101000_z, 1000_z )
					| transformed( [&] (const size_t &number_size) {
						std::cerr << "make_heap__vs__sort " << number_size << "\n";
						const auto mean_results = average_results_over(
							500,
							[&] {
								return generate_data( gen, number_size );
							},
							[&] (const doub_vec &arg_data) {
								doub_vec bob{ arg_data };
								const auto start_time = steady_clock::now();
								make_heap( begin( bob ), end( bob ) );
								return 1000.0 * duration_cast<duration<double>>( steady_clock::now() - start_time ).count();
							},
							[&] (const doub_vec &arg_data) {
								doub_vec bob{ arg_data };
								const auto start_time = steady_clock::now();
								sort( begin( bob ), end( bob ) );
								return 1000.0 * duration_cast<duration<double>>( steady_clock::now() - start_time ).count();
							}
						);

						return tuple_to_string_join( tuple_cat( make_tuple( number_size ), mean_results ), " " ) + "\n";
					} )
			);
		}

		else {
			constexpr size_t THREE_STRATEGIES_BASE_NUM =    125'000;
			write_streamables_range_to_file(
				"graphs/three_strategies.data." + to_lower_copy( get_platform_string() ),
				irange(   5_z,  505_z,   5_z )
					| transformed( [&] (const size_t &number_size) {
						std::cerr << "three_strategies " << number_size << "\n";
						const auto mean_results = average_results_over(
							500,
							[&] {
								return generate_data( gen, THREE_STRATEGIES_BASE_NUM + number_size );
							},
							[&] (const doub_vec &arg_data) {
								doub_vec bob{ cbegin( arg_data ), next( cbegin( arg_data ), THREE_STRATEGIES_BASE_NUM ) };
								doub_vec new_nums{ next( cbegin( arg_data ), THREE_STRATEGIES_BASE_NUM ), cend( arg_data ) };

								const doub_vec expected = push_pop_answer( bob, new_nums );

								const auto start_time = steady_clock::now();
								for (double &new_num : new_nums) {
									const auto max_itr = max_element( begin( bob ), end( bob) );
									swap( *max_itr, new_num );
								}
								const auto durn = 1000.0 * duration_cast<duration<double>>( steady_clock::now() - start_time ).count();

								if ( expected != new_nums ) {
									throw out_of_range( "argh three_strategies max_element()" );
								}

								return durn;
							},
							[&] (const doub_vec &arg_data) {
								doub_vec bob{ cbegin( arg_data ), next( cbegin( arg_data ), THREE_STRATEGIES_BASE_NUM ) };
								doub_vec new_nums{ next( cbegin( arg_data ), THREE_STRATEGIES_BASE_NUM ), cend( arg_data ) };


								// Pushing then popping can give wrong answer if new value is larger than any other present
								// and appeared to be a bit slower anyway
								//
								// I also tried a cheeky:
								//  * push the new value to the back of the vector
								//  * call a single pop_heap()
								// ...which showed a slight improvement (681ms -> 398ms) after 5 million steps on Clang
								// but it was a bit slower on GCC (621ms -> 713ms)
								const doub_vec expected = push_pop_answer( bob, new_nums );

								const auto start_time = steady_clock::now();
								make_heap( begin( bob ), end( bob ) );
								for (double &new_num : new_nums) {
									pop_heap( begin( bob ), end( bob ) );
									swap( bob.back(), new_num );
									push_heap( begin( bob ), end( bob ) );
								}

								const auto durn = 1000.0 * duration_cast<duration<double>>( steady_clock::now() - start_time ).count();

								if ( expected != new_nums ) {
									throw out_of_range( "argh three_strategies heap (pop then push)" );
								}

								return durn;
							},
							[&] (const doub_vec &arg_data) {
								doub_vec bob{ cbegin( arg_data ), next( cbegin( arg_data ), THREE_STRATEGIES_BASE_NUM ) };
								doub_vec new_nums{ next( cbegin( arg_data ), THREE_STRATEGIES_BASE_NUM ), cend( arg_data ) };

								const doub_vec expected = push_pop_answer( bob, new_nums );

								const auto start_time = steady_clock::now();
								sort( begin( bob ), end( bob ) );
								for (double &new_num : new_nums) {
									const auto new_posn_itr = lower_bound( begin( bob ), end( bob ), new_num );
									swap( bob.back(), new_num );
									if ( new_posn_itr != cend( bob ) && next( new_posn_itr ) != cend( bob ) ) {
										std::rotate( new_posn_itr, prev( end( bob ) ), end( bob ) );
									}
								}

								const auto durn = 1000.0 * duration_cast<duration<double>>( steady_clock::now() - start_time ).count();

								if ( expected != new_nums ) {
									throw out_of_range( "argh three_strategies sort()" );
								}

								return durn;
							}
						);

						return tuple_to_string_join( tuple_cat( make_tuple( number_size ), mean_results ), " " ) + "\n";
					} )
			);
		}

	}
	catch (const exception &ex) {
		const string error_message( "Exception : "s + ex.what() );
		perror( error_message.c_str() );
	};
}

