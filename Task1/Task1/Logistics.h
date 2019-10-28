#pragma once
#include "Storage.h"
#include "Vehicle.h"

class Logistics
{
	vector<vector<double>> minDistances;
	vector<vector<double>> graph;
	vector<Storage*> storages;
	vector<Load*> loads;
	vector<Vehicle*> vehicles;

	Storage* storage(int id);
	Load* load(int type);
	int now = 0;
	Storage* priorityStorage(Load* load);
	Vehicle* priorityVehicle(Storage* storage, Load* load);
	void setGraph();
	double minDistance(vector<double>& dist, vector<bool>& sptSet);
	void dijkstra();
public:
	vector<vector<Path*>> minPathes;
	void load(const char* fName);
	void simulate(int endTime);
};
