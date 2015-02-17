#ifndef ROCKET_HPP
#define ROCKET_HPP

#include "fairings.hpp"
#include "stage.hpp"

#include <vector>

class RocketModel;

class Rocket
{
public:
	using container_stage_t = std::vector<Stage>;

	Rocket() = delete;
	Rocket(const RocketModel& model, double payload_mass_);
	Rocket(Rocket&&) = default;
	~Rocket() = default;

	const std::string name;
	const double payload_mass;
	const Fairings fairings;

	const container_stage_t& stages() const;

	double currentMass() const;

	double grossMass() const;

	double dryMass() const;

	double currentThrust() const;

	double totalLength() const;

	double maximumDiameter() const;

	void fire();

private:
	container_stage_t m_stages;
	bool m_is_firing = false;
};

#endif // ROCKET_HPP
