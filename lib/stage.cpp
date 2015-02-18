#include "stage.hpp"

#include <cassert>

Stage::Stage(StageModel model_) : model(model_)
{
}

double Stage::currentMass() const
{
	return m_filling_rate * model.fuelMass() + model.dry_mass;
}

double Stage::currentThrust() const
{
	if(m_filling_rate > 0)
		return model.thrust;
	return 0;
}

double Stage::fillingRate() const
{
	assert(0 <= m_filling_rate && m_filling_rate <= 1);
	return m_filling_rate;
}

void Stage::burn(double dt)
{
	assert(0 <= m_filling_rate && m_filling_rate <= 1);
	m_filling_rate -= dt * model.burnRate();
	if(m_filling_rate < 0)
		m_filling_rate = 0;
	assert(0 <= m_filling_rate && m_filling_rate <= 1);
}
