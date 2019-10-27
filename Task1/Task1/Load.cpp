#include "Load.h"

Load::Load(int type, double volume, double weight)
{
	this->type = type;
	this->volume = volume;
	this->weight = weight;
}

PeriodicalLoad::PeriodicalLoad(Load* _load, int _period, int _increase)
{
	load = _load;
	period = _period;
	increase = _increase;
	nextTime = _period;
	quantity = _increase;
}
