#ifndef ROCKETMODEL_HPP
#define ROCKETMODEL_HPP

#include "fairings.hpp"
#include "stagemodel.hpp"

#include <vector>

class RocketModel
{
public:
	RocketModel() = delete;
	RocketModel(RocketModel&&) = default;
	RocketModel(const RocketModel&) = default;
	~RocketModel() = default;

	using stages_container_t = std::vector<StageModel>;

	const std::string name;
	const stages_container_t stages;
	const Fairings fairings;

	static RocketModel fromJson(std::istream& i);
	static RocketModel fromJson(const nlohmann::json& js);

private:
	RocketModel(std::string name_, stages_container_t stages_, const Fairings& fairings_);
};

#endif // ROCKETMODEL_HPP
