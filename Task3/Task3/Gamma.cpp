#include "Gamma.h"

Gamma::Gamma()
{
	count++;
	N = count;
}

Gamma::~Gamma()
{
	S -= N;
}

int Gamma::Schange(int currS)
{
	if (useCount == 1)
	{
		currS = (currS - N) / 2 - N;
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
