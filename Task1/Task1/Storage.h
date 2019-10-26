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
		StorageDistance(Storage* storage, double distance)
		{
			this->storage = storage;
			this->distance = distance;
		}
	};
	int id;
	vector<StorageDistance*> neighboringStorages;
	double X() 
	{
		return this->x;
	}
	double Y()
	{
		return this->y;
	}
	Storage(vector<int>& loadingLoads, vector<StorageDistance*>& neighboringStorages = DEFAULT_VECTOR_SD,
		vector<Load*>& unloadingLoads = DEFAULT_VECTOR_L, vector<Load*>& spawningLoads = DEFAULT_VECTOR_L, int spawnPeriod = -1)
	{
		this->loadingLoads = loadingLoads;
		this->unloadingLoads = unloadingLoads;
		this->spawningLoads = spawningLoads;
		this->spawnPeriod = spawnPeriod;
		this->neighboringStorages = neighboringStorages;
	}
private:
	static vector<StorageDistance*> DEFAULT_VECTOR_SD;
	static vector<Load*> DEFAULT_VECTOR_L;
	double x;
	double y;
	vector<Load*> spawningLoads;
	int spawnPeriod;
	vector<Load*> unloadingLoads;
	vector<int> loadingLoads;
};



