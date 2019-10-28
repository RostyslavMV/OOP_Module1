#pragma once
#include "Load.h"
#include "Storage.h"
#include <vector>
#include <string>
#include <queue>

using std::vector;
using std::string;
using std::deque;

class Path
{
public:
	// Absolute time, starting from first point of path
	int startTime;
	// Absolute time, starting from second point of path
	int nextStartTime = -1;
	// Absolute time of arrival
	int finishTime = -1;

	deque <Storage*> storages;
	Storage* last();
	bool contains(Storage* storage);
	string toStr();
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

struct DeliverRequest {
public:
	int time;
	int quantity;
	DeliverRequest(int time, int quantity);
};

class Vehicle
{
	bool air;
	vector<Cargo*> cargo;
	double maxLoadVolume;
	double maxLoadWeight;
	double speed;
	int loadTime;
	int unloadTime;
	// Path contains storage
	bool pathContainsStorage(Storage* storage);
	// Dispatch time from storage on path
	int dispatchTime(Storage* storage);
	Storage* lastStorage();

	// Free weight after unloading on storage
	double freeWeight(Storage* storage);

	// Free volume after unloading on storage
	double freeVolume(Storage* storage);

	// Ñheck if unloads on storage
	bool unloading(Storage* storage);
	// Ñheck if loads on storage
	bool loading(Storage* storage);
	// Remove cargo after unloading
	void removeCargo(Storage* storage);
public:
	Vehicle(double maxVolume, double maxWeight, double speed, Storage* wStorage, int lTime, int uTime, bool air);
	bool isAir() { return air; }
	int id;
	Path* path = new Path();

	// Place of waiting when empty
	Storage* waitingStorage;

	// Possible time of arival on storage
	int possibleTime(Storage* storage);

	// Returns time of arival on storage and how much load it can deliver
	DeliverRequest request(Load* l, Storage* storage);

	// Add cargo for transportation
	void addCargo(Load* l, int quantity, Storage* sender, Storage* recipient);
	
	// Add path of moving
	void addPath(Storage* from, Storage* to, int time);
	void recalc(int time);
};

struct VehicleRequest {
public:
	Vehicle* vehicle;
	int time;
	int quantity;
};