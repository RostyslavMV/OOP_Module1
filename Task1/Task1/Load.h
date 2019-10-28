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
public:
	int increase;
	PeriodicalLoad(Load* load, int period, int increase);
	int quantity = 0;
	int period;
	Load* load;
	int nextTime;
};

