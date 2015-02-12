#ifndef STAGEMODEL_HPP
#define STAGEMODEL_HPP

#include <string>

namespace nlohmann
{
	class json;
}

struct StageModel
{
	const std::string name;
	const double length;
	const double diameter;
	const double dry_mass;
	const double gross_mass;
	const double thrust;
	const double isp;
	const double burn_time;
	const std::string fuel;

	static StageModel fromJson(const nlohmann::json& json);
};

#endif // STAGEMODEL_HPP
