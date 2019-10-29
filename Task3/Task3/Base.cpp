#include "Base.h"
#include "Base1.h"
#include "Base2.h"

void Base::countUseCount()
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

void Base::setUseCount(int useCount_)
{
	useCount = useCount_;
}
