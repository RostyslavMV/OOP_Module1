#include <iostream>
#include "Function.h"

using std::cout;
using std::endl;

int main()
{
	Function f;
	cout << f.func(5) << endl;
	cout << f.func(-57) << endl;
	cout << f.func(5.7) << endl;
	string s = "ass bsd bhs bb asdas   k bsa bbb bk   b";
	cout << f.func(s) << endl;
	pair<string, double> pair(s, 145.76);
	cout << f.func(pair) << endl;
	vector<double> vec{ 5.164,7.789,6.1,123.1 };
	cout << f.func(vec) << endl;
	cout << f.func('a') << endl;
	return 0;
}
