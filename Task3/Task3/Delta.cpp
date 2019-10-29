#include "Delta.h"

Delta::Delta()
{
	count++;
	N = count;
}

Delta::~Delta()
{
	S = S + 3 * N - 7;
}

int Delta::Schange(int currS)
{
	if (useCount == 1)
	{
		currS = (currS+3*N-7) / 2 - N;
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
