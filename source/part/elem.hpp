#ifndef SOURCE_PART_ELEM_H
#define SOURCE_PART_ELEM_H

#include <boost/optional.hpp>

#include <functional>

namespace hh::part { class cont; }

namespace hh::part {

	namespace detail {
		/// \brief TODOCUMENT
		struct silent_construct_tag final {};

		/// \brief TODOCUMENT
		enum class dtor_volume : bool {
			NOISY, ///< TODOCUMENT
			SILENT ///< TODOCUMENT
		};
	}

	/// \brief TODOCUMENT
	class elem {
	private:
		friend void swap(elem &,
		                 elem &);

		/// \brief TODOCUMENT
		std::reference_wrapper<const cont> parent;

		/// \brief TODOCUMENT
		double value = 0.0 / 0.0;

		/// \brief TODOCUMENT
		detail::dtor_volume volume = detail::dtor_volume::NOISY;

		elem(detail::silent_construct_tag,
		     elem &&);

		elem & silent_move_assign(elem &&);

	public:
		explicit elem(const cont &);
		explicit elem(const cont &,
		              double);
		elem(const elem &);
		elem(elem &&);
		~elem();


		elem & silence();

		elem & operator=(const elem &);
		elem & operator=(elem &&);
		const double & get_value() const;
		boost::optional<size_t> get_index() const;
	};

	bool operator<(const elem &,
	               const elem &);

	void swap(elem &,
	          elem &);

}

#endif
