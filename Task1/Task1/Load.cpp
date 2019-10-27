#include "Load.h"

Load::Load(int type, double volume, double weight)
{
	this->type = type;
	this->volume = volume;
	this->weight = weight;
}

PeriodicalLoad::PeriodicalLoad(Load* load, int period, int increase)
{
	this->load = load;
	this->period = period;
	this->increase = increase;
	this->nextTime = period;
	this->quantity = increase;
}
