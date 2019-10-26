#pragma once
#include "Load.h"
#include "Storage.h"
#include "Storages.h"
#include <vector>

using std::vector;

class Vehicle
{
public:
	struct LoadStartDestination
	{
		Load* load;
		Storage* start;
		Storage* destination;
		LoadStartDestination()
		{

		}
		LoadStartDestination(Load* load, Storage* start, Storage* destination)
		{
			this->load = load;
			this->start = start;
			this->destination = destination;
		}
	};
	int id;
	double currentTimeLeft() {
		(currentRoadLength - currentRoadProgress) / velocity;
	}
	void NewLoad(Load* load, Storage* start, Storage* destination) {
		onboardLoads.push_back(new LoadStartDestination(load,start,destination));
		CalcualateRoadLength();
	}
protected:
	Storages* storagesSystem;
	double maxLoadVolume;
	double maxLoadWeight;
	int velocity;

	Storage* currentStart;
	Storage* currentDestination;
	double currentLoadVolume;
	double currentLoadWeight;
	double currentRoadLength;
	double currentRoadProgress;
		
	vector<LoadStartDestination*> onboardLoads;
	virtual void CalcualateRoadLength() = 0;
};

