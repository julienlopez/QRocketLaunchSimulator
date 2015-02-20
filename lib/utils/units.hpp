#ifndef UNITS_HPP
#define UNITS_HPP

#include "utils/point.hpp"

#include <boost/units/quantity.hpp>
#include <boost/units/systems/si.hpp>

namespace utils
{
	namespace units
	{
		using acceleration = boost::units::quantity<boost::units::si::acceleration>;
		using force = boost::units::quantity<boost::units::si::force>;
		using frequency = boost::units::quantity<boost::units::si::frequency>;
		using length = boost::units::quantity<boost::units::si::length>;
		using mass = boost::units::quantity<boost::units::si::mass>;
		using area = boost::units::quantity<boost::units::si::area>;
		using time = boost::units::quantity<boost::units::si::time>;
		using velocity = boost::units::quantity<boost::units::si::velocity>;
		using pressure = boost::units::quantity<boost::units::si::pressure>;

		using acceleration_vector = utils::point3d<acceleration>;
		using velocity_vector = utils::point3d<velocity>;
		using position_vector = utils::point3d<length>;
	}
}

#endif // UNITS_HPP
