#include "rocket.hpp"
#include "rocketmodel.hpp"

#include <numeric>

Rocket::Rocket(const RocketModel& model, double payload_mass_)
	: name(model.name)
	, payload_mass(payload_mass_)
	, fairings(model.fairings)
{
	for(const auto& stage_model : model.stages)
		m_stages.emplace_back(stage_model);
}

auto Rocket::stages() const -> const container_stage_t &
{
	return m_stages;
}

utils::units::mass Rocket::currentMass() const
{
	utils::units::mass res = 0;
	for(const auto& stage : m_stages)
		res += stage.currentMass();
	return res;
}

utils::units::mass Rocket::grossMass() const
{
	utils::units::mass res = 0;
	for(const auto& stage : m_stages)
		res += stage.model.gross_mass;
	return res;
}

utils::units::mass Rocket::dryMass() const
{
	utils::units::mass res = 0;
	for(const auto& stage : m_stages)
		res += stage.model.dry_mass;
	return res;
}

utils::units::force Rocket::currentThrust() const
{
	if(!m_is_firing || m_stages.empty())
		return 0;
	return m_stages.front().currentThrust();
}

utils::units::length Rocket::totalLength() const
{
	utils::units::length res = fairings.length;
	for(const auto& stage : m_stages)
		res += stage.model.length;
	return res;
}

utils::units::length Rocket::maximumDiameter() const
{
	utils::units::length res = fairings.diameter;
	for(const auto& stage : m_stages)
		res = std::max(stage.model.diameter, res);
	return res;
}

void Rocket::fire()
{
	m_is_firing = true;
}

void Rocket::burn(utils::units::time dt)
{
	if(!m_stages.empty())
		m_stages.front().burn(dt);
}
