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
private:
	double X;
	double Y;
	vector<StorageDistance> neighboringStorages;
	vector<Load> unloadingLoads;
	vector<int> loadingLoads;
};

