#include <iostream>
#include "Logistics.h"


int main()
{
	Logistics l;
	l.load("data.txt");
	l.simulate(100);
}

