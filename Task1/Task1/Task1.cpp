#include <iostream>
#include "Logistics.h"


int main()
{
	logistic.load("data.txt");
	logistic.simulate(500);
	logistic.outVehicles(1, 1, 1);
}

