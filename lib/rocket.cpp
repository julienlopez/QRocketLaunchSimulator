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

double Rocket::currentMass() const
{
	double res = 0;
	for(const auto& stage : m_stages)
		res += stage.currentMass();
	return res;
}

double Rocket::grossMass() const
{
	double res = 0;
	for(const auto& stage : m_stages)
		res += stage.model.gross_mass;
	return res;
}

double Rocket::dryMass() const
{
	double res = 0;
	for(const auto& stage : m_stages)
		res += stage.model.dry_mass;
	return res;
}

double Rocket::currentThrust() const
{
	return 0;
}

double Rocket::totalLength() const
{
	double res = fairings.length;
	for(const auto& stage : m_stages)
		res += stage.model.length;
	return res;
}

double Rocket::maximumDiameter() const
{
	double res = fairings.diameter;
	for(const auto& stage : m_stages)
		res = std::max(stage.model.diameter, res);
	return res;
}
