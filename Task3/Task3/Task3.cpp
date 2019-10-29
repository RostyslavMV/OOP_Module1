#include <iostream>
#include <vector>
#include "Alpha.h"
#include "Beta.h"
#include "Gamma.h"
#include "Delta.h"

using std::vector;
using std::cout;

int main()
{
	vector<shared_ptr<Base1>> base1elems;
	vector<shared_ptr<Base2>> base2elems;
	for (int i = 0; i < 10; i++)
	{
		base1elems.push_back(shared_ptr<Alpha>(new Alpha()));
		base1elems.push_back(shared_ptr<Beta>(new Beta()));
		base2elems.push_back(shared_ptr<Gamma>(new Gamma()));
		base2elems.push_back(shared_ptr<Delta>(new Delta()));
	}
	while (!base1elems.empty())
	{
		base1elems.erase(base1elems.begin());
	}
	while (!base2elems.empty())
	{
		base2elems.erase(base2elems.begin());
	}
	cout << "S = " << S;
}

