#ifndef ROCKETMODEL_HPP
#define ROCKETMODEL_HPP

#include "stagemodel.hpp"

#include <vector>

class RocketModel
{
public:
	RocketModel() = delete;

	using stages_container_t = std::vector<StageModel>;

	const std::string name;
	const stages_container_t stages;

	static RocketModel fromJson(std::istream& i);
	static RocketModel fromJson(const nlohmann::json& js);

private:
	RocketModel(std::string name_, stages_container_t stages_);
};

#endif // ROCKETMODEL_HPP
