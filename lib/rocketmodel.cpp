#include "rocketmodel.hpp"

#include "utils/json_helper.hpp"

#include "external/json.h"

using nlohmann::json;

RocketModel RocketModel::fromJson(std::istream& i)
{
	json js;
	i >> js;
	return fromJson(js);
}

RocketModel RocketModel::fromJson(const nlohmann::json& js)
{
	const auto name = utils::json_helper::getAndCheckType
		<std::string>(js, "name", json::value_t::string);

	stages_container_t stages;
	const auto s = utils::json_helper::getAndCheckType
		<json::array_t>(js, "stages", json::value_t::array);
	for(const auto& stage : s)
	{
		stages.push_back(StageModel::fromJson(stage));
	}

	return {std::move(name), std::move(stages)};
}

RocketModel::RocketModel(std::string name_, stages_container_t stages_)
	: name(std::move(name_))
	, stages(std::move(stages_))
{
}
