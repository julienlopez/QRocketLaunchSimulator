#include "stage.hpp"

Stage::Stage(StageModel model_) : model(model_)
{
}

double Stage::currentMass() const
{
	return model.gross_mass;
}

double Stage::currentThrust() const
{
	return model.thrust;
}
