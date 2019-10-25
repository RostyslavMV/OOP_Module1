#pragma once
#include "Load.h"
#include <vector>

using std::vector;

class Vehicle
{
public:
	int id;
protected:
	double maxLoadVolume;
	double maxLoadWeight;
	double currentLoadVolume;
	double currentLoadWeight;
	double currentRoadLength;
	double currentRoadProgress;
	int velocity;
	vector<Load> onboardLoads;
};

