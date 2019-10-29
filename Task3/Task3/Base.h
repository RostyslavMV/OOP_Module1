#pragma once
#include <memory>

class Base1;
class Base2;

using std::shared_ptr;

class Base
{
protected:
	int useCount = 0;
public:
	shared_ptr<Base1> base1;
	shared_ptr<Base2> base2;
	void countUseCount();
	void setUseCount(int useCount_);
};



