#include "engine.hpp"
#include "engine_impl.hpp"
#include "rocket.hpp"

Engine::Engine(Rocket& rocket_, const Body& launch_body_)
	: etl::utils::pimpl<EngineImpl>(std::ref(rocket_), std::cref(launch_body_))
{
}

Engine::~Engine()
{
}

const Body& Engine::body() const
{
	return get().body();
}

auto Engine::state() const -> const State &
{
	return get().state();
}

utils::units::time Engine::currentTime() const
{
	return get().currentTime();
}

utils::units::length Engine::altitude() const
{
	return get().altitude();
}

utils::units::acceleration_vector Engine::currentAcceleration() const
{
	return get().currentAcceleration();
}

void Engine::tick(utils::units::time dt)
{
	get().tick(dt);
}
