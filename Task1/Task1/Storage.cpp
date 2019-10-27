#include "Storage.h"

Neighbor::Neighbor(Storage* storage, double distance)
{
	this->storage = storage;
	this->distance = distance;
}

Storage::Storage(int id, double x, double y)
{
	this->id = id;
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