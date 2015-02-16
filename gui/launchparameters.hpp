#ifndef LAUNCHPARAMETERS_HPP
#define LAUNCHPARAMETERS_HPP

#include "rocketmodel.hpp"

struct LaunchParameters
{
	RocketModel rocket_model;
	double payload_mass;
	double start_gravity_turn;
	double end_gravity_turn;
	double angle;
};

#endif // LAUNCHPARAMETERS_HPP
