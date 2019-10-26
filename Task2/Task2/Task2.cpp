#include <iostream>
#include "Function.h"

using std::cout;
using std::endl;

int main()
{
	Function f;
	cout << "f(int =5) = " << f.func(5) << endl;
	cout << "f(int = -57) = " << f.func(-57) << endl;
	cout << "f(double = 5.7) = " << f.func(5.7) << endl;
	string s = "ass bsd bhs bb asdas   k bsa bbb bk   b";
	cout << "f(string = \"ass bsd bhs bb asdas   k bsa bbb bk   b\") = " << f.func(s) << endl;
	pair<string, double> pair(s, 145.76);
	cout << "f(pair<string, double> = \"ass bsd bhs bb asdas   k bsa bbb bk   b\" , 145.76) = " << f.func(pair) << endl;
	vector<double> vec{ 5.164,7.789,6.1,123.1 };
	cout << "f(vec{ 5.164,7.789,6.1,123.1 }) = " << f.func(vec) << endl;
	cout << "f(other type (char 'a')) = " << f.func('a') << endl;
	return 0;
}
