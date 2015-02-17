#include "engine.hpp"
#include "engine_impl.hpp"
#include "rocket.hpp"

Engine::Engine(Rocket& rocket_, const position_t& initial_position)
	: etl::utils::pimpl<EngineImpl>(std::ref(rocket_), std::cref(initial_position))
{
}

Engine::~Engine()
{
}

auto Engine::state() const -> const State &
{
	return get().state();
}

double Engine::currentTime() const
{
    return get().currentTime();
}

double Engine::altitude() const
{
    return get().altitude();
}

void Engine::tick(double dt)
{
	get().tick(dt);
}
