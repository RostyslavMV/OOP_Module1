#pragma once
#include "Load.h"
#include <vector>

using std::vector;

class Storage
{
public:
	int id;
	double X() 
	{
		return this->x;
	}
	double Y()
	{
		return this->y;
	}
private:
	struct StorageDistance
	{
		Storage* storage;
		double distance;
	};
	double x;
	double y;
	vector<StorageDistance> neighboringStorages;
	vector<Load*> unloadingLoads;
	vector<int> loadingLoads;
};



