#pragma once
#include "Load.h"
#include "Storage.h"
#include <vector>

using std::vector;

class Path
{
	vector <Storage*> storages;
	int startTime;
};

class Cargo
{
	Load* load;
	Storage* sender;
	Storage* recipient;
};

class Vehicle
{
public:
	Path* path = nullptr;
	Storage* waitingStorage;

protected:
	double maxLoadVolume;
	double maxLoadWeight;
	int speed;
};

