#ifndef FAIRINGS_HPP
#define FAIRINGS_HPP

#include "utils/units.hpp"

#include <string>

namespace nlohmann
{
	class json;
}

struct Fairings
{
	const utils::units::length length;
	const utils::units::length diameter;

	static Fairings fromJson(const nlohmann::json& js);
};

#endif // FAIRINGS_HPP
