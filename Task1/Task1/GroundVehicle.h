#pragma once
#include "Vehicle.h"
class GroundVehicle :
	public Vehicle
{
private:
	void CalcualateRoadLength() override
	{
		this->currentRoadLength = storagesSystem->GetRoadLength(currentStart, currentDestination);
	}
public:
	GroundVehicle(Storages* storagesSystem, double maxLoadVolume, double maxLoadWeight, int velocity)
	{
		this->storagesSystem = storagesSystem;
		this->maxLoadVolume = maxLoadVolume;
		this->maxLoadWeight = maxLoadWeight;
		this->velocity = velocity;
	}
};

