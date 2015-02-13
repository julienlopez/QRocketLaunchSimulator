#ifndef ROCKET_HPP
#define ROCKET_HPP

#include "stage.hpp"

#include <vector>

class RocketModel;

class Rocket
{
public:
	using container_stage_t = std::vector<Stage>;

	Rocket(const RocketModel& model);
	~Rocket() = default;

	const std::string name;

	const container_stage_t& stages() const;

    double currentMass() const;

    double grossMass() const;

    double dryMass() const;

private:
	container_stage_t m_stages;
};

#endif // ROCKET_HPP
