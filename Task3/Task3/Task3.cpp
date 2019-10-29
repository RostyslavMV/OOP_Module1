#include <iostream>
#include <vector>
#include "Alpha.h"
#include "Beta.h"
#include "Gamma.h"
#include "Delta.h"
#include "Predictor.h"

using std::vector;
using std::cout;
using std::endl;

int main()
{
	Predictor<Base1> predictor1;
	Predictor<Base2> predictor2;
	vector<shared_ptr<Base1>> base1elems;
	vector<shared_ptr<Base2>> base2elems;
	for (int i = 0; i < 10; i++)
	{
		base1elems.push_back(shared_ptr<Alpha>(new Alpha()));
		base1elems[base1elems.size() - 1]->setUseCount(base1elems[base1elems.size() - 1].use_count());
		base1elems.push_back(shared_ptr<Beta>(new Beta()));
		base1elems[base1elems.size() - 1]->setUseCount(base1elems[base1elems.size() - 1].use_count());
		base2elems.push_back(shared_ptr<Gamma>(new Gamma()));
		base2elems[base2elems.size() - 1]->setUseCount(base2elems[base2elems.size() - 1].use_count());
		base2elems.push_back(shared_ptr<Delta>(new Delta()));
		base2elems[base2elems.size() - 1]->setUseCount(base2elems[base2elems.size() - 1].use_count());
	}
	cout << "Predicted S = " << predictor1.predictS(base1elems) << endl;
	while (!base1elems.empty())
	{
		base1elems.erase(base1elems.begin());
	}
	cout << "S = " << S<<endl;
	cout << "Predicted S = " << predictor2.predictS(base2elems) << endl;
	while (!base2elems.empty())
	{
		base2elems.erase(base2elems.begin());
	}
	cout << "S = " << S << endl;
}

