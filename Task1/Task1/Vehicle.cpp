#include "Vehicle.h"
#include <iostream>

using std::invalid_argument;

CanDeliver::CanDeliver(int time, int quantity)
{
	this->time = time;
	this->quantity = quantity;
}

CanDeliver Vehicle::request(Load* l, Storage* sender, Storage* recipient)
{
	int time;
	int volumeQuantity;
	int weightQuantity;
	if (path == nullptr)
	{
		time = moveTime(waitingStorage, sender);
		volumeQuantity = maxLoadVolume / l->volume;
		weightQuantity = maxLoadWeight / l->weight;
	}
	else if (pathContainsStorage(sender))
	{
		time = dispatchTime(sender);
		volumeQuantity = freeVolume(sender) / l->volume;
		weightQuantity = freeWeight(sender) / l->weight;
	}
	else
	{
		Storage* last = lastStorage();
		time = dispatchTime(last) + moveTime(last, sender);
		volumeQuantity = maxLoadVolume / l->volume;
		weightQuantity = maxLoadWeight / l->weight;
	}
	int quantity;
	if (volumeQuantity < weightQuantity)
		quantity = volumeQuantity;
	else
		quantity = weightQuantity;
	return CanDeliver(time, quantity);
}

void Vehicle::addCargo(Load* l, int quantity, Storage* sender, Storage* recipient)
{
	cargo.push_back(new Cargo(l, quantity, sender, recipient));
}

bool Vehicle::pathContainsStorage(Storage* storage)
{
	if (path != nullptr)
		return path->contains(storage);
	return false;
}

int Vehicle::dispatchTime(Storage* storage)
{
	if (path == nullptr || !path->contains(storage))
	{
		throw invalid_argument("error\n");
		return INT_MAX;
	}
	int time = 0;
	std::vector<Storage*>::iterator it;
	Storage* prev = nullptr;
	for (it = path->storages.begin(); it != path->storages.end(); it++)
	{
		Storage* s = (*it);
		if (unloading(s)) time += unloadTime;
		if (loading(s)) time += loadTime;
		if (prev) time += moveTime(prev, s);
		if (s == storage) break;
	}
	return path->startTime + time;
}

Storage* Vehicle::lastStorage()
{
	if (path != nullptr)
		return path->last();
	else
		return waitingStorage;
}

double Vehicle::freeVolume(Storage* storage)
{
	double v = 0;
	std::vector<Cargo*>::iterator it;
	for (it = cargo.begin(); it != cargo.end(); it++)
	{
		Cargo* c = (*it);
		if (c->recipient == storage)
			v += c->load->volume * c->quantity;
	}
	return maxLoadVolume - v;
}

double Vehicle::freeWeight(Storage* storage)
{
	double w = 0;
	std::vector<Cargo*>::iterator it;
	for (it = cargo.begin(); it != cargo.end(); it++)
	{
		Cargo* c = (*it);
		if (c->recipient == storage)
			w += c->load->weight * c->quantity;
	}
	return maxLoadWeight - w;
}

bool Vehicle::unloading(Storage* storage)
{
	std::vector<Cargo*>::iterator it;
	for (it = cargo.begin(); it != cargo.end(); it++)
	{
		Cargo* c = (*it);
		if (c->recipient == storage)
			return true;
	}
	return false;
}

bool Vehicle::loading(Storage* storage)
{
	std::vector<Cargo*>::iterator it;
	for (it = cargo.begin(); it != cargo.end(); it++)
	{
		Cargo* c = (*it);
		if (c->sender == storage)
			return true;
	}
	return false;
}

Storage* Path::last()
{
	if (!storages.empty())
		return storages.back();
}

bool Path::contains(Storage* storage)
{
	return std::find(storages.begin(), storages.end(), storage) != storages.end();
}

Cargo::Cargo(Load* load, int quantity, Storage* sender, Storage* recipient)
{
	this->load = load;
	this->quantity = quantity;
	this->sender = sender;
	this->recipient = recipient;
}
