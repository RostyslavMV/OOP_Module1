#pragma once
#include <memory>
#include <vector>
#include "Base1.h"
#include "Base2.h"
#include "Global.h"

using std::vector;

template<typename T>
class Predictor
{
public:
	int predictS(vector<shared_ptr<T>> vec);
};

template<typename T>
inline int Predictor<T>::predictS(vector<shared_ptr<T>> vec)
{
	int currentS = S;
	for (shared_ptr<T> t: vec )
	{
		currentS = t->Schange(currentS);
	}
	return currentS;
}
