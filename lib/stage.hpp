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

	/**
	 * @brief fillingRate current filling rate of the stage, 0 <= FR <= 1
	 * @return
	 * @postconditions 0 <= FR <= 1
	 */
	double fillingRate() const;

	void burn(double dt);

private:
	double m_filling_rate = 1;
};

#endif // STAGE_HPP
