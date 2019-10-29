#include "Base2.h"

int Base2::count = 0;

Base2::~Base2()
{
	S = S / 2 - N;
}
