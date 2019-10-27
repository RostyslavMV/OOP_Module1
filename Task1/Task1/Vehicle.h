#pragma once
#include "Load.h"
#include "Storage.h"
#include <vector>

using std::vector;

class Path
{
public:
	int startTime;
	vector <Storage*> storages;
	Storage* last();
	bool contains(Storage* storage);
};

class Cargo
{
public:
	Load* load;
	int quantity;
	Storage* sender;
	Storage* recipient;
};

struct CanDeliver {
	int time;
	int quantity;
public:
	struct CanDeliver(int time, int quantity);
};

class Vehicle
{
public:
	Path* path = nullptr;
	Storage* waitingStorage;
	CanDeliver request(Load* l, Storage* sender, Storage* recipient);
protected:
	vector<Cargo*> cargo;
	double maxLoadVolume;
	double maxLoadWeight;
	int speed;
	int loadTime;
	int unloadTime;
	virtual int moveTime(Storage* from, Storage* to) = 0;
	bool pathContainsStorage(Storage* storage);
	int dispatchTime(Storage* storage);
	Storage* lastStorage();
	double freeVolume(Storage* storage);
	double freeWeight(Storage* storage);
	bool unloading(Storage* storage);
	bool loading(Storage* storage);
};

