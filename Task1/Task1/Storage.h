#pragma once
#include "Load.h"
#include <vector>

using std::vector;

class Storage;

class Neighbor
{
public:
	Neighbor(Storage* storage, double distance);
	Storage* storage;
	double distance;
};

class Storage
{
	double x;
	double y;
	int id;
public:
	Storage(double x, double y);
	int Id() { return id; };
	double X() { return this->x; }
	double Y() { return this->y; }
	void addNeighbor(Storage* storage, double distance);

	int nextInLoadTime = -1;
	vector<Neighbor*> neighbores;
	vector<PeriodicalLoad*> inLoads;
	vector<PeriodicalLoad*> outLoads;

	void addInLoad(Load* load, int period, int quantity);
	void addOutLoad(Load* load, int period, int quantity);
	bool canOutload(Load* load, int time);
};



