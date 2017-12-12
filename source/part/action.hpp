#ifndef SOURCE_PART_ACTION_H
#define SOURCE_PART_ACTION_H

#include <boost/variant.hpp>

namespace hh::part {

	struct construct_action final {
	};

	struct construct_dflt_action final {

	};

	struct copy_assign_action final {
		// from " << arg_elem.get_index() << " to " << get_index() << "
	};

	struct copy_construct_action final {
		// from " << arg_elem.get_index() << " to " << get_index() << "
	};

	struct destruct_action final {
		// " << get_index() << "
	};

	struct less_action final {
		// between " << arg_lhs.get_index() << " and " << arg_rhs.get_index() << "
	};

	struct move_assign_action  final {
		// from " << arg_elem.get_index() << " to " << get_index() << "
	};

	struct move_construct_action final {
		// from " << arg_elem.get_index() << " to " << get_index() << "
	};

	struct swap_action final {
		// between " << arg_lhs.get_index() << " and " << arg_rhs.get_index() << "
	};

	using action = boost::variant<
		construct_action,
		construct_dflt_action,
		copy_assign_action,
		copy_construct_action,
		destruct_action,
		less_action,
		move_assign_action,
		move_construct_action,
		swap_action
	>;
}

#endif
