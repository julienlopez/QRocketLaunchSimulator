#ifndef FAIRINGS_HPP
#define FAIRINGS_HPP

#include <string>

namespace nlohmann
{
	class json;
}

struct Fairings
{
	const double length;
	const double diameter;

	static Fairings fromJson(const nlohmann::json& js);
};

#endif // FAIRINGS_HPP
