#pragma once

class Load
{
public:
	int type;
	double volume;
	double weight;
	Load(int type, double volume, double weight);
};

class PeriodicalLoad {
	int increase;
	int quantity = 0;
public:
	PeriodicalLoad(Load* load, int period, int increase);
	int period;
	Load* load;
	int nextTime;
};

