#pragma once
#include "Load.h"
#include "Storage.h"
#include "Storages.h"
#include <vector>

using std::vector;

class Vehicle
{
public:
	int id;
	double currentTimeLeft() {
		(currentRoadLength - currentRoadProgress) / velocity;
	}
	void NewLoad(Load load, Storage* start, Storage* destination) {
		onboardLoads.push_back(load);
		this->start = start;
		this->destination = destination;
		CalcualateRoadLength();
	}
protected:
	Storages* storagesSystem;
	double maxLoadVolume;
	double maxLoadWeight;
	int velocity;

	Storage* start;
	Storage* destination;
	double currentLoadVolume;
	double currentLoadWeight;
	double currentRoadLength;
	double currentRoadProgress;
		
	vector<Load> onboardLoads;
	virtual void CalcualateRoadLength() = 0;
};

