#pragma once
#include "Load.h"
#include <vector>

using std::vector;

struct StorageDistance
{
	Storage* storage;
	double distance;
};
class Storage
{
public:
	int id;
	double X() 
	{
		return this->X;
	}
	double Y()
	{
		return this->Y;
	}
private:
	double X;
	double Y;
	vector<StorageDistance> neighboringStorages;
	vector<Load> unloadingLoads;
	vector<int> loadingLoads;
};

