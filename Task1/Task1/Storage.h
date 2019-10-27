#pragma once
#include "Load.h"
#include <vector>

using std::vector;

class Storage;

class Neighbor
{
	Storage* storage;
	double distance;
public:
	Neighbor(Storage* storage, double distance);
};

class Storage
{
private:
	double x;
	double y;
	int id;
public:
	Storage(int id, double x, double y);
	int Id() { return id; };
	double X() { return this->x; }
	double Y() { return this->y; }
	vector<Neighbor*> neighbores;
	vector<PeriodicalLoad*> inLoads;
	vector<PeriodicalLoad*> outLoads;
	void addNeighbor(Storage* storage, double distance);
	void addInLoad(Load* load, int period, int quantity);
	void addOutLoad(Load* load, int period, int quantity);
};



