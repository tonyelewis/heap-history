#ifndef SOURCE_PART_CONT_H
#define SOURCE_PART_CONT_H

#include <boost/optional.hpp>

#include "part/elem.hpp"

#include <tuple>
#include <type_traits>
#include <vector>

namespace hh::part {

	template <typename...> class type_printer;

	/// \brief TODOCUMENT
	using elem_vec = std::vector<elem>;

	/// \brief TODOCUMENT
	class cont {
	private:
		/// \brief TODOCUMENT
		elem_vec elements;

		template <typename... Ts>
		void emplace_back_impl(std::true_type,
		                       Ts &&...args
		                       ) {
			elements.emplace_back( std::forward<Ts>( args )... );
		}

		template <typename... Ts>
		void emplace_back_impl(std::false_type,
		                       Ts &&...args
		                       ) {
			elements.emplace_back( *this, std::forward<Ts>( args )... );
		}

	public:
		/// \brief TODOCUMENT
		using const_iterator = elem_vec::const_iterator;

		/// \brief TODOCUMENT
		using iterator       = elem_vec::iterator;

		cont() noexcept = default;

		iterator insert(const_iterator,
		                const elem &);
		iterator insert(const_iterator,
		                elem &&);
		iterator erase(const_iterator);

		template <typename... Ts>
		void emplace_back(Ts &&...args
		                  ) {
			emplace_back_impl(
				std::bool_constant<
				sizeof...( Ts ) == 1
				&&
				std::is_same< std::decay_t< std::tuple_element_t< 0, std::tuple< Ts...> > >, elem >::value
				>{},
				std::forward<Ts>( args )...
			);
		}
		auto back() -> decltype( auto ) {
			return elements.back();
		}
		auto front() -> decltype( auto ) {
			return elements.front();
		}

		const_iterator begin() const;
		const_iterator end() const;
		iterator begin();
		iterator end();

		boost::optional<size_t> get_index(const elem &) const;
	};
}

#endif
