#pragma once
#include "Load.h"
#include "Storage.h"
#include <vector>
#include <cmath>

using std::vector;

class Path
{
public:
	int startTime;
	double length;
	vector <Storage*> storages;
	Storage* last();
	bool contains(Storage* storage);
	Path(vector<Storage*> storages)
	{
		this->storages = storages;
	}
	Path(vector<Storage*> storages, double length)
	{
		this->storages = storages;
		this->length = length;
	}
};

class Cargo
{
public:
	Cargo(Load* load, int quantity, Storage* sender, Storage* recipient);
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
	void addCargo(Load* l, int quantity, Storage* sender, Storage* recipient);
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

