#include "Alpha.h"

Alpha::Alpha()
{
	count++;
	N = count;
}

Alpha::~Alpha()
{
	S = S - N + 17;
}

int Alpha::Schange(int currS)
{
	if (useCount == 1)
	{
		currS = 2 * (currS - N + 17) + N - 17;
		if (base1)
		{
			currS = base1->Schange(currS);
		}
		if (base2)
		{
			currS = base2->Schange(currS);
		}
	}
	useCount--;
	return currS;
}
