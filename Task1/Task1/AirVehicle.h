#pragma once
#include "Vehicle.h"
class AirVehicle :
	public Vehicle
{
public:
	void CalcualateRoadLength() override
	{
		double dX = this->start->X() - this->destination->X();
		double dY = this->start->Y() - this->destination->Y();
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

