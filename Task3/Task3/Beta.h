#pragma once
#include "Base1.h"
class Beta :
	public Base1
{
public:
	Beta();
	~Beta();
	int Schange(int currS) override;
};

