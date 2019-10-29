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
