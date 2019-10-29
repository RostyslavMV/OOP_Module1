#pragma once
#include "Global.h"
#include <memory>

using std::shared_ptr;

class Base2;

class Base1
{
protected:
	static int count;
	shared_ptr<Base1> base1;
	shared_ptr<Base2> base2;	
public:
	int N = 1;
	virtual ~Base1();
};

