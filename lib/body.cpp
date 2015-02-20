#include "body.hpp"

using boost::units::si::joules;
using boost::units::si::kelvins;
using boost::units::si::kilograms;
using boost::units::si::meters;
using boost::units::si::meters_per_second_squared;
using boost::units::si::moles;
using boost::units::si::pascals;
using boost::units::si::seconds;

Body::Body(const utils::units::mass& mass_, const utils::units::length& radius_)
	: mass(mass_)
	, radius(radius_)
{
}

utils::units::pressure Body::atmosphericPressure(const utils::units::length& altitude) const
{
	static const auto p_zero = 101325 * pascals;
	static const auto g = 9.80665 * meters_per_second_squared;
	static const auto M = 0.0289644 * kilograms / moles;
	static const auto R = 8.31447 * joules / moles / kelvins;
	static const auto T_zero = 288.15 * kelvins;
	const auto factor = exp(-(g * M * altitude / R / T_zero).value())
						* boost::units::si::si_dimensionless;
	return factor * p_zero;
}
