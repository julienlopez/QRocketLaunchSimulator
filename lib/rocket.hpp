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

	utils::units::mass currentMass() const;

	utils::units::mass grossMass() const;

	utils::units::mass dryMass() const;

	utils::units::force currentThrust() const;

	utils::units::length totalLength() const;

	utils::units::length maximumDiameter() const;

	void fire();

	void burn(utils::units::time dt);

private:
	container_stage_t m_stages;
	bool m_is_firing = false;
};

#endif // ROCKET_HPP
