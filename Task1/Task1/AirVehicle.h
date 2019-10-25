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
};

