#ifndef ROCKET_HPP
#define ROCKET_HPP

#include "stage.hpp"

#include <vector>

class RocketModel;

class Rocket
{
public:
	using container_stage_t = std::vector<Stage>;

	Rocket() = delete;
	Rocket(const RocketModel& model, double payload_mass_);
	~Rocket() = default;

	const std::string name;
	const double payload_mass;

	const container_stage_t& stages() const;

	double currentMass() const;

	double grossMass() const;

	double dryMass() const;

	double currentThrust() const;

private:
	container_stage_t m_stages;
};

#endif // ROCKET_HPP
