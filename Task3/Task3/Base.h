#pragma once
#include <memory>

class Base1;
class Base2;

using std::shared_ptr;

class Base
{
protected:
	shared_ptr<Base1> base1;
	shared_ptr<Base2> base2;
	int useCount = 0;
public:
	void countUseCount()
	{
		if (base1)
		{
			base1->setUseCount(base1.use_count());
			base1->countUseCount();
		}
		if (base2)
		{
			base2->setUseCount(base2.use_count());
			base2->countUseCount();
		}
	}
	void setUseCount(int useCount_)
	{
		useCount = useCount_;
	}
};

