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