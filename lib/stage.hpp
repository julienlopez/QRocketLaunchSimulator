#ifndef STAGE_HPP
#define STAGE_HPP

#include "stagemodel.hpp"

class Stage
{
public:
	Stage(StageModel model_);

	const StageModel model;

	double currentMass() const;

	double currentThrust() const;
};

#endif // STAGE_HPP
