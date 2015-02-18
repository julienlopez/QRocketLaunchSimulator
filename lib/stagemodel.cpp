#include "stagemodel.hpp"

#include "utils/json_helper.hpp"

#include "external/json.h"

using nlohmann::json;

StageModel StageModel::fromJson(const json& json)
{
	if(json.type() != json::value_t::object)
		throw std::runtime_error("invalid json object, invalid stage");

	return {utils::json_helper::getAndCheckType<std::string>(json, "name", json::value_t::string),
			utils::json_helper::getAndCheckNumber<double>(json, "length"),
			utils::json_helper::getAndCheckNumber<double>(json, "diameter"),
			utils::json_helper::getAndCheckNumber<double>(json, "dry_mass"),
			utils::json_helper::getAndCheckNumber<double>(json, "gross_mass"),
			utils::json_helper::getAndCheckNumber<double>(json, "thrust"),
			utils::json_helper::getAndCheckNumber<double>(json, "isp"),
			utils::json_helper::getAndCheckNumber<double>(json, "burn_time"),
			utils::json_helper::getAndCheckType<std::string>(json, "fuel", json::value_t::string)};
}

double StageModel::burnRate() const
{
	return 1 / burn_time;
}

double StageModel::fuelMass() const
{
	return gross_mass - dry_mass;
}
