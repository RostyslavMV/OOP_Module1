#pragma once
#include "Global.h"
#include "Base.h"
#include "Base1.h"

class Base2 : public Base
{
protected:
	static int count;
public:
	virtual int Schange(int currS) = 0;
	int N = 1;
	virtual ~Base2();
};

