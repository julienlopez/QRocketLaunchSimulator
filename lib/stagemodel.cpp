#include "stagemodel.hpp"

#include "utils/json_helper.hpp"

#include "external/json.h"

using nlohmann::json;

StageModel StageModel::fromJson(const json& json)
{
	if(json.type() != json::value_t::object)
		throw std::runtime_error("invalid json object, invalid stage");

	return {
		utils::json_helper::getAndCheckType<std::string>(json, "name", json::value_t::string),
		utils::json_helper::getAndCheckNumber<double>(json, "length") * boost::units::si::meters,
		utils::json_helper::getAndCheckNumber<double>(json, "diameter") * boost::units::si::meters,
		utils::json_helper::getAndCheckNumber<double>(json, "dry_mass")
		* boost::units::si::kilograms,
		utils::json_helper::getAndCheckNumber<double>(json, "gross_mass")
		* boost::units::si::kilograms,
		utils::json_helper::getAndCheckNumber<double>(json, "thrust") * boost::units::si::newtons,
		utils::json_helper::getAndCheckNumber<double>(json, "isp") * boost::units::si::seconds,
		utils::json_helper::getAndCheckNumber<double>(json, "burn_time")
		* boost::units::si::seconds,
		utils::json_helper::getAndCheckType<std::string>(json, "fuel", json::value_t::string)};
}

utils::units::frequency StageModel::burnRate() const
{
	return 1 * boost::units::si::si_dimensionless / burn_time;
}

utils::units::mass StageModel::fuelMass() const
{
	return gross_mass - dry_mass;
}
