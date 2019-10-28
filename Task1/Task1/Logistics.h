#pragma once
#include "Storage.h"
#include "Vehicle.h"

class Logistics
{
	vector<Storage*> storages;
	vector<Load*> loads;
	vector<Vehicle*> vehicles;

	vector<vector<double>> minDistances;
	vector<vector<double>> graph;

	Storage* storage(int id);
	Load* load(int type);

	// Storage to transport load
	Storage* priorityStorage(Load* load, Storage* recipient, int time);
	// Choose vehicle
	Vehicle* priorityVehicle(Storage* sender, Storage* recipient, Load* load, int now);

	// Recalculating path and load for time (Clean passed path, unloaded loads
	void recalcVehicle(int time);
	void setGraph();
	double minDistance(vector<double>& dist, vector<bool>& sptSet);
	void dijkstra();
public:
	// Distance between a and b storages
	double distance(Storage* a, Storage* b, bool useAir);
	// Loading data from file for modeling
	void load(const char* fName);
	void simulate(int endTime);
	void outVehicles(int time, int storageId, int loadType, int quantity);
};

extern Logistics logistic;