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
}

void Storage::addOutLoad(Load* load, int period, int quantity)
{
	outLoads.push_back(new PeriodicalLoad(load, period, quantity));
}