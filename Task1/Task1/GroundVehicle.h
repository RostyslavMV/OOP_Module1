#pragma once
#include "Vehicle.h"
class GroundVehicle :
	public Vehicle
{
private:
	void CalcualateRoadLength() override
	{
		this->currentRoadLength = storagesSystem->GetRoadLength(start, destination);
	}
};

