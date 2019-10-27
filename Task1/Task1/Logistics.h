#pragma once
#include "Storage.h"

class Logistics
{
	vector<Storage*> storages;
	vector<Load*> loads;
	Storage* storage(int id);
	Load* load(int type);
public:
	void load(const char* fName);
	void simulate(int endTime);
};
