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
