#ifndef BODY_HPP
#define BODY_HPP

#include <utils/units.hpp>

struct Body
{
	Body(const utils::units::mass& mass_, const utils::units::length& radius_);

	const utils::units::mass mass;
	const utils::units::length radius;
};

#endif // BODY_HPP
