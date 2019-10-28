#include <iostream>
#include "Logistics.h"


int main()
{
	logistic.load("data.txt");

	int endTime = 500;
	logistic.simulate(endTime);
	logistic.outVehicles(endTime, 1, 1, 1);
}

