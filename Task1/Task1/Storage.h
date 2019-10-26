#pragma once
#include "Load.h"
#include <vector>

using std::vector;

class Storage
{
public:
	struct StorageDistance
	{
		Storage* storage;
		double distance;
	};
	int id;
	vector<StorageDistance> neighboringStorages;
	double X() 
	{
		return this->x;
	}
	double Y()
	{
		return this->y;
	}
private:
	static vector<StorageDistance> DEFAULT_VECTOR;
	double x;
	double y;
	vector<Load*> spawningLoads;
	int spawnPeriod;
	vector<Load*> unloadingLoads;
	vector<int> loadingLoads;
	Storage(vector<int>& loadingLoads, vector<Load*>& unloadingLoads, vector<Load*>& spawningLoads,
		int spawnPeriod, vector<StorageDistance>& neighboringStorages = DEFAULT_VECTOR)
	{
		this->loadingLoads = loadingLoads;
		this->unloadingLoads = unloadingLoads;
		this->spawningLoads = spawningLoads;
		this->spawnPeriod = spawnPeriod;
		this->neighboringStorages = neighboringStorages;
	}
};



