#pragma once
#include "Global.h"
#include "Base.h"
#include "Base2.h"

class Base1: public Base
{
protected:
	static int count;
public:
	virtual int Schange(int currS) = 0;
	int N = 1;
	virtual ~Base1();
};

