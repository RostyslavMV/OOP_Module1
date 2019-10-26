#pragma once
class Load
{
public:
	int type;
	double volume;
	double weight;
	Load(int type, double volume, double weight)
	{
		this->type = type;
		this->volume = volume;
		this->weight = weight;
	}
};

