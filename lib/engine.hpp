#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "utils/units.hpp"

#include <etl/utils/pimpl.hpp>
#include <etl/utils/noncopiable.hpp>

class EngineImpl;
class Rocket;

class Engine : private etl::utils::pimpl<EngineImpl>, private etl::utils::noncopiable
{
public:
	using position_t = utils::units::position_vector;
	using velocity_t = utils::units::velocity_vector;

	struct State
	{
		position_t position;
		velocity_t velocity;
	};

	Engine(Rocket& rocket_, const position_t& initial_position);
	~Engine();

	const State& state() const;

	utils::units::time currentTime() const;

	/**
	 * @brief altitude returns the altitude, relative to the ground.
	 * @return
	 */
	utils::units::length altitude() const;

	utils::units::acceleration_vector currentAcceleration() const;

	void tick(utils::units::time dt);
};

#endif // ENGINE_HPP
