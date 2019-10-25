#pragma once
#include "Load.h"
#include "Storage.h"
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
	}
protected:
	Storage* start;
	Storage* destination;
	double maxLoadVolume;
	double maxLoadWeight;
	double currentLoadVolume;
	double currentLoadWeight;
	double currentRoadLength;
	double currentRoadProgress;
	int velocity;
	vector<Load> onboardLoads;
	virtual void CalcualateRoadLength() = 0;
};

