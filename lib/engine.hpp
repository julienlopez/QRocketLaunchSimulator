#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "utils/point.hpp"

#include <etl/utils/pimpl.hpp>
#include <etl/utils/noncopiable.hpp>

class EngineImpl;
class Rocket;

class Engine : private etl::utils::pimpl<EngineImpl>, private etl::utils::noncopiable
{
public:
	using position_t = utils::point3d<double>;
	using velocity_t = utils::point3d<double>;

	struct State
	{
		position_t position;
		velocity_t velocity;
	};

	Engine(Rocket& rocket_, const position_t& initial_position);
	~Engine();

	const State& state() const;

	double currentTime() const;

	/**
	 * @brief altitude returns the altitude, relative to the ground.
	 * @return
	 */
	double altitude() const;

	void tick(double dt);
};

#endif // ENGINE_HPP
