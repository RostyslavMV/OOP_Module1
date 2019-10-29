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
