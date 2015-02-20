#include "engine_impl.hpp"
#include "rocket.hpp"

#include <boost/units/cmath.hpp>

EngineImpl::EngineImpl(Rocket& rocket_, const Body& launch_body_)
	: m_body(launch_body_)
	, m_rocket(rocket_)
	, m_state({Engine::position_t{0, launch_body_.radius + m_rocket.totalLength(), 0},
			   Engine::velocity_t{0}})
	, m_initial_position({0, launch_body_.radius, 0})
{
}

const Body& EngineImpl::body() const
{
	return m_body;
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

utils::units::force EngineImpl::gravityForce() const
{
	using boost::units::si::cubic_meters;
	using boost::units::si::kilograms;
	using boost::units::si::seconds;
	static auto G = 6.67384E-11 * cubic_meters / kilograms / seconds / seconds;
	const auto vector = m_state.position; // because center of attracting body on {0, 0, 0} for now
	return G * m_rocket.currentMass() * m_body.mass / vector.norm2();
}

utils::point3d<utils::units::acceleration> EngineImpl::currentAcceleration() const
{
	const auto value = (m_rocket.currentThrust() - gravityForce()) / m_rocket.currentMass();
	return {0, value, 0};
}

void EngineImpl::tick(utils::units::time dt)
{
	m_rocket.burn(dt);
	if(m_state.position == utils::units::position_vector{0 * boost::units::si::meters})
		return;
	const auto acceleration = currentAcceleration();
	m_state.velocity += dt * acceleration;
	m_state.position += m_state.velocity * dt;
	m_current_time += dt;
}
