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
	PeriodicalLoad(Load* _load, int _period, int _increase);
	int period;
	Load* load;
	int nextTime;
};

