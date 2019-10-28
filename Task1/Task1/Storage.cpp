#include "Storage.h"

int nextStorageId = 0;

Storage::Storage(double x, double y)
{
	this->id = nextStorageId++;
	this->x = x;
	this->y = y;
}

void Storage::addNeighbor(Storage* storage, double distance)
{
	neighbores.push_back(new Neighbor(storage, distance));
}

void Storage::addInLoad(Load* load, int period, int quantity)
{
	inLoads.push_back(new PeriodicalLoad(load, period, quantity));
	if (nextInLoadTime == -1 || nextInLoadTime < period)
		nextInLoadTime = period;
}

void Storage::addOutLoad(Load* load, int period, int quantity)
{
	outLoads.push_back(new PeriodicalLoad(load, period, quantity));
}

bool Storage::canOutload(Load* load, int time)
{
	for (PeriodicalLoad* pl : outLoads)
	{
		if (pl->load == load)
		{
			while (pl->nextTime <= time)
			{
				pl->quantity += pl->increase;
				pl->nextTime += pl->period;
			}
			if (pl->quantity > 0)
				return true;
		}
	}
	return false;
}

Neighbor::Neighbor(Storage* storage, double distance)
{
	this->storage = storage;
	this->distance = distance;
}
