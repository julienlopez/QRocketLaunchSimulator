#ifndef STAGEMODEL_HPP
#define STAGEMODEL_HPP

#include "utils/units.hpp"

#include <string>

namespace nlohmann
{
	class json;
}

struct StageModel
{
	const std::string name;
	const utils::units::length length;
	const utils::units::length diameter;
	const utils::units::mass dry_mass;
	const utils::units::mass gross_mass;
	const utils::units::force thrust;
	const utils::units::time isp;
	const utils::units::time burn_time;
	const std::string fuel;

	static StageModel fromJson(const nlohmann::json& json);

	utils::units::frequency burnRate() const;

	utils::units::mass fuelMass() const;
};

#endif // STAGEMODEL_HPP
