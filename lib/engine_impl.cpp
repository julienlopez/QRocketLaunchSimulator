#include "engine_impl.hpp"
#include "rocket.hpp"

#include <boost/units/cmath.hpp>

EngineImpl::EngineImpl(Rocket& rocket_, const Engine::position_t& initial_position)
	: m_rocket(rocket_)
	, m_state({initial_position + Engine::position_t{0, m_rocket.totalLength(), 0},
			   Engine::velocity_t{0}})
	, m_initial_position(initial_position)
{
}

const Engine::State& EngineImpl::state() const
{
	return m_state;
}

utils::units::time EngineImpl::currentTime() const
{
	return m_current_time;
}

utils::units::length EngineImpl::altitude() const
{
	const utils::units::position_vector relative_pos = m_initial_position - m_state.position;
	return (relative_pos).norm();
}

utils::point3d<utils::units::acceleration> EngineImpl::currentAcceleration() const
{
	return {0, m_rocket.currentThrust() / m_rocket.currentMass(), 0};
}

void EngineImpl::tick(utils::units::time dt)
{
	m_rocket.burn(dt);
    const auto acceleration = currentAcceleration();
    m_state.velocity += dt * acceleration;
	m_state.position += m_state.velocity * dt;
	m_current_time += dt;
}
