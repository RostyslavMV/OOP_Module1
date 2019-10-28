#include "Vehicle.h"
#include <iostream>
#include "Logistics.h"
#include <algorithm>

int nextVehicleId = 1;

DeliverRequest::DeliverRequest(int time, int quantity)
{
	this->time = time;
	this->quantity = quantity;
}

Vehicle::Vehicle(double maxVolume, double maxWeight, double speed, Storage* wStorage, int lTime, int uTime, bool air)
{
	id = nextVehicleId++;
	this->maxLoadVolume = maxVolume;
	this->maxLoadWeight = maxWeight;
	this->speed = speed;
	this->waitingStorage = wStorage;
	this->loadTime = lTime;
	this->unloadTime = uTime;
	this->air = air;
}

DeliverRequest Vehicle::request(Load* l, Storage* sender, int now)
{
	int volumeQuantity;
	int weightQuantity;
	int time = possibleTime(sender, now);
	if (pathContainsStorage(sender))
	{
		volumeQuantity = (int)floor(freeVolume(sender) / l->volume);
		weightQuantity = (int)floor(freeWeight(sender) / l->weight);
	}
	else
	{
		volumeQuantity = (int)floor(maxLoadVolume / l->volume);
		weightQuantity = (int)floor(maxLoadWeight / l->weight);
	}
	int quantity;
	if (volumeQuantity < weightQuantity)
		quantity = volumeQuantity;
	else
		quantity = weightQuantity;
	return DeliverRequest(time, quantity);
}

void Vehicle::addCargo(Load* l, int quantity, Storage* sender, Storage* recipient)
{
	cargo.push_back(new Cargo(l, quantity, sender, recipient));
}

void Vehicle::addPath(Storage* from, Storage* to, int time)
{
	if (path->storages.empty())
	{
		path->startTime = time;
		path->storages.push_back(from);
		path->storages.push_back(to);
		path->finishTime = dispatchTime(path->last(), true);
		path->nextStartTime = path->finishTime;
	}
	else
	{
		if (!path->contains(from))
		{
			path->storages.push_back(from);
			path->storages.push_back(to);
		}
		else
			if (!path->contains(from, to))
				path->storages.push_back(to);
		path->finishTime = dispatchTime(path->last(), true);
		if (path->nextStartTime > path->finishTime)
			std::cout << "***error";
	}
}

void Vehicle::recalc(int time)
{
	while (path->nextStartTime != -1 && path->nextStartTime <= time) // Видаляєм пройдені маршрути
	{
		if (path->storages.size() == 2) // прибули в кінцеву точку
		{
			path->nextStartTime = -1;
			path->storages.clear();
			cargo.clear();
		}
		else
		{
			int t = path->startTime;
			path->nextStartTime = dispatchTime(path->storages[1], false);
			path->startTime = t;
			Storage* st = path->storages[0];
			removeCargo(st);
			path->storages.erase(path->storages.begin());
		}
	}
}

bool Vehicle::pathContainsStorage(Storage* storage)
{
	if (path != nullptr)
		return path->contains(storage);
	return false;
}

int Vehicle::dispatchTime(Storage* storage, bool last)
{
	if (!path->contains(storage))
	{
		std::cout << "error\n";
		return INT_MAX;
	}
	int time = 0;
	Storage* prev = nullptr;

	for (Storage* s : path->storages)
	{
		if (unloading(s)) time += unloadTime;
		if (loading(s)) time += loadTime;
		if (prev) time += (int)ceil(logistic.distance(prev, s, air) / speed);
		prev = s;
		if (s == storage && !last) break;
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
	for (Cargo* c : cargo)
	{
		if (c->recipient != storage)
			v += c->load->volume * c->quantity;
	}
	if (v < maxLoadVolume)
		return maxLoadVolume - v;
	else
		return 0;
}

int Vehicle::possibleTime(Storage* storage, int now)
{
	int time;
	if (path->contains(storage))
	{
		time = path->startTime;
		Storage* prev = nullptr;
		for (Storage* s : path->storages)
		{
			if (s == storage && path->nextStartTime < now)
				break;
			if (unloading(s)) time += unloadTime;
			if (loading(s)) time += loadTime;
			if (prev) time += (int)ceil(logistic.distance(prev, s, air) / speed);
			prev = s;
		}
	}
	else
	{
		Storage* last;
		if (path->storages.empty())
		{
			last = waitingStorage;
			time = now;
		}
		else
		{
			last = path->last();
			time = path->finishTime;
		}
		time += (int)ceil(logistic.distance(last, storage, air) / speed);
	}
	if (time < now)
		time = now; 
	return time;;
}

double Vehicle::freeWeight(Storage* storage)
{
	double w = 0;
	for (Cargo* c : cargo)
	{
		if (c->recipient != storage)
			w += c->load->weight * c->quantity;
	}
	if (w < maxLoadWeight)
		return maxLoadWeight - w;
	else
		return 0;
}

bool Vehicle::unloading(Storage* storage)
{
	for (Cargo* c : cargo)
	{
		if (c->recipient == storage)
			return true;
	}
	return false;
}

bool Vehicle::loading(Storage* storage)
{
	for (Cargo* c : cargo)
	{
		if (c->sender == storage)
			return true;
	}
	return false;
}

void Vehicle::removeCargo(Storage* storage)
{
	cargo.erase(std::remove_if(cargo.begin(), cargo.end(),
		[storage](Cargo*& v)
		{
			return v->recipient == storage;
		}), cargo.end());
}


Storage* Path::last()
{
	if (!storages.empty())
		return storages.back();
	return nullptr;
}

bool Path::contains(Storage* storage)
{
	return std::find(storages.begin(), storages.end(), storage) != storages.end();
}

bool Path::contains(Storage* first, Storage* second)
{
	bool firstFound = false;
	for (Storage* s : storages)
	{
		if (firstFound)
		{
			if (s == second) return true;
		}
		else
			if (s == first)
				firstFound = true;
	}
	return false;
}

string Path::toStr()
{
	string ret = "";
	for (Storage* s : storages)
	{
		if (ret.length() != 0)
			ret += " -> ";
		ret += std::to_string(s->Id());
	}
	return ret;
}

Cargo::Cargo(Load* load, int quantity, Storage* sender, Storage* recipient)
{
	this->load = load;
	this->quantity = quantity;
	this->sender = sender;
	this->recipient = recipient;
}
