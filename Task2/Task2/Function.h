#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <cmath>

using std::string;
using std::to_string;
using std::vector;
using std::istringstream;
using std::pair;

class Function
{
private:
	int IntPow(int arg, int pow)
	{
		int ret = 0;
		for (int i = 1; i < pow; i++)
		{
			ret += arg;
		}
	}
	string IntName(int a)
	{
		string ret;
		switch (a / 100)
		{
		case 1:
			ret += "one ";
			break;
		case 2:
			ret += "two ";
			break;
		case 3:
			ret += "three ";
			break;
		case 4:
			ret += "four ";
			break;
		case 5:
			ret += "five ";
			break;
		case 6:
			ret += "six ";
			break;
		case 7:
			ret += "seven ";
			break;
		case 8:
			ret += "eight ";
			break;
		case 9:
			ret += "nine ";
			break;
		}
		ret += "hundred ";
		switch ((a % 100) / 10)
		{
		case 2:
			ret += "twenty ";
			break;
		case 3:
			ret += "thirty ";
			break;
		case 4:
			ret += "forty ";
			break;
		case 5:
			ret += "fifty ";
			break;
		case 6:
			ret += "sixty ";
			break;
		case 7:
			ret += "seventy ";
			break;
		case 8:
			ret += "eighty ";
			break;
		case 9:
			ret += "ninety ";
			break;
		}
		if (a % 100 >= 10 & a % 100 < 20)
		{
			switch (a % 100)
			{
			case 10:
				ret += "ten ";
				break;
			case 11:
				ret += "eleven ";
				break;
			case 12:
				ret += "twelve ";
				break;
			case 13:
				ret += "thirteen ";
				break;
			case 14:
				ret += "fourteen ";
				break;
			case 15:
				ret += "fifteen ";
				break;
			case 16:
				ret += "sixteen ";
				break;
			case 17:
				ret += "seventeen ";
				break;
			case 18:
				ret += "eighteen ";
				break;
			case 19:
				ret += "nineteen";
				break;
			}
		}
		else
		{
			switch (a % 10)
			{
			case 1:
				ret += "one ";
				break;
			case 2:
				ret += "two ";
				break;
			case 3:
				ret += "three ";
				break;
			case 4:
				ret += "four ";
				break;
			case 5:
				ret += "five ";
				break;
			case 6:
				ret += "six ";
				break;
			case 7:
				ret += "seven ";
				break;
			case 8:
				ret += "eight ";
				break;
			case 9:
				ret += "nine ";
				break;
			}
		}
		return ret;
	}
public:
	template <typename T>
	string func(T argument)
	{
		return "sorry try again please";
	}
	template <>
	string func(int argument)
	{
		int a;
		string ret;
		if (argument >= 0)
			a = (argument * argument) % 117;
		else
			a = (IntPow(argument, 5) + IntPow(argument, 3)) % 217;
		int bil = a / 1000000000;
		if (bil > 0)
		{
			ret += IntName(bil) + "billions ";
		}
		int mil = (a - (bil * 1000000000)) / 1000000;
		if (mil > 0)
		{
			ret += IntName(mil) + "millions ";
		}
		int th = (a - (bil * 1000000000) - (mil * 1000000)) / 1000;
		if (th > 0)
		{
			ret += IntName(th) + "thousands ";
		}
		int rest = a - (bil * 1000000000) - (mil * 1000000) - (th * 1000);
		if (rest > 0)
		{
			ret += IntName(rest);
		}
	}
	template <>
	string func(double argument)
	{
		string a, ret;
		a = to_string(sin(argument + 317));
		string s = a.substr(s.find('.', 2));
		ret = IntName(((int)s.at(0) - 48) * 10 + (int)s.at(1) - 48);
		return ret;
	}
	template <>
	string func(double argument)
	{
		string a, ret;
		a = to_string(sin(argument + 317));
		string s = a.substr(s.find('.', 2));
		ret = IntName(((int)s.at(0) - 48) * 10 + (int)s.at(1) - 48);
		return ret;
	}
	template <>
	string func(string argument)
	{
		string ret;
		vector<string> words;
		istringstream iss(argument);
		for (string s; iss >> s; )
			words.push_back(s);
		for (int i = words.size() - 1; i >= 0; i--)
		{
			ret += words[i] + " ";
		}
		if (ret.at(ret.size() - 1) == ' ')
			ret.erase(ret.size() - 1);
		return ret;
	}
	template <typename T1, typename T2>
	string func(pair<T1, T2> pair)
	{
		string ret;
		string s1 = func(T1), s2 = func(T2);
		istringstream iss1(s1), iss2(s2);
		string buff1, buff2;
		while (iss1 >> buff1 && iss2 >> buf2)
		{
			ret += buff1 + " " + buff2 + " ";
		}
		while (iss1 >> buff1)
		{
			ret += buff1 + " ";
		}
		while (iss2 >> buff2)
		{
			ret += buff2 + " ";
		}
		if (ret.at(ret.size() - 1) == ' ')
			ret.erase(ret.size() - 1);
		return ret;
	}

};

