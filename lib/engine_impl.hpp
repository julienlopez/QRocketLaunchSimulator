#ifndef ENGINE_IMPL_HPP
#define ENGINE_IMPL_HPP

#include "engine.hpp"

class EngineImpl
{
public:
	EngineImpl(Rocket& rocket_, const Engine::position_t& initial_position);
	~EngineImpl() = default;

	const Engine::State& state() const;

	utils::units::time currentTime() const;

	utils::units::length altitude() const;

	utils::point3d<utils::units::acceleration> currentAcceleration() const;

	void tick(utils::units::time dt);

private:
	Rocket& m_rocket;
	Engine::State m_state;
	Engine::position_t m_initial_position;
	utils::units::time m_current_time = 0;
};

#endif // ENGINE_IMPL_HPP
