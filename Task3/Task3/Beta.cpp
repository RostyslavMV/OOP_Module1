#include "Beta.h"

Beta::Beta()
{
	count++;
	N = count;
}

Beta::~Beta()
{
	S = S + N;
}

int Beta::Schange(int currS)
{
	if (useCount == 1)
	{
		currS = 2 * (currS + N) + N - 17;
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

