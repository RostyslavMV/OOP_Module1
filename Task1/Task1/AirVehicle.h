#pragma once
#include "Vehicle.h"
class AirVehicle :
	public Vehicle
{
public:
	void CalcualateRoadLength() override
	{
		double dX = this->currentStart->X() - this->currentDestination->X();
		double dY = this->currentStart->Y() - this->currentDestination->Y();
		this->currentRoadLength = sqrt(dX * dX + dY * dY);
	}
	AirVehicle(Storages* storagesSystem, double maxLoadVolume, double maxLoadWeight, int velocity)
	{
		this->storagesSystem = storagesSystem;
		this->maxLoadVolume = maxLoadVolume;
		this->maxLoadWeight = maxLoadWeight;
		this->velocity = velocity;
	}
};

