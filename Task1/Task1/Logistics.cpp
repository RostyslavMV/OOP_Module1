#include "Logistics.h"
#include <fstream>
#include <sstream>
#include <iostream>

std::string getVal(std::string s, const char* key) {
	int p1 = s.find(key, 0);
	p1 = s.find("=", p1);
	p1++;
	int p2 = s.find(";", p1);
	if (p2 == 0) p2 = s.length() - 1;
	return s.substr(p1, p2 - p1);
}

int getInt(std::string s, const char* key) {
	std::string ss = getVal(s, key);
	int ret = std::stoi(ss);
	return ret;
}

double getDbl(std::string s, const char* key) {
	std::string ss = getVal(s, key);
	int ret = std::stof(ss);
	return ret;
}

Storage* Logistics::storage(int id)
{
	std::vector<Storage*>::iterator it;
	for (it = storages.begin(); it != storages.end(); it++)
	{
		if ((*it)->Id() == id)
			return *it;
	}
	return nullptr;
}

Load* Logistics::load(int type)
{
	std::vector<Load*>::iterator it;
	for (it = loads.begin(); it != loads.end(); it++)
	{
		if ((*it)->type == type)
			return *it;
	}
	return nullptr;
}

void Logistics::load(const char* fName)
{
	std::ifstream file(fName);
	std::string s;
	int prev = 0, pos = 0;
	while (std::getline(file, s))
	{
		if (s.rfind("storage", 0) == 0)
		{
			int id = getInt(s, "id");
			double x = getDbl(s, "x");
			double y = getDbl(s, "y");
			Storage* storage = new Storage(id, x, y);
			storages.push_back(storage);
		}
		else if (s.rfind("road", 0) == 0)
		{
			int a = getInt(s, "a");
			int b = getInt(s, "b");
			double l = getDbl(s, "l");
			Storage* stA = storage(a);
			Storage* stB = storage(b);
			if (stA == nullptr)
				std::cout << "storage " << a << " not found";
			else if (stB == nullptr)
				std::cout << "storage " << b << " not found";
			else
			{
				stA->addNeighbor(stB, l);
				stB->addNeighbor(stA, l);
			}
		}
		else if (s.rfind("load", 0) == 0)
		{
			int t = getInt(s, "t");
			double v = getDbl(s, "v");
			double w = getDbl(s, "w");
			loads.push_back(new Load(t, v, w));
		}
		else if (s.rfind("inload", 0) == 0)
		{
			int l = getInt(s, "l");
			int _s = getInt(s, "s");
			int p = getInt(s, "p");
			int q = getInt(s, "q");
			Storage* st = storage(_s);
			Load* ld = load(l);
			if (st == nullptr)
				std::cout << "inload: storage " << st << " not found";
			else if (ld == nullptr)
				std::cout << "inload: load " << l << " not found";
			else
			{
				st->addInLoad(ld, p, q);
			}
		}
		else if (s.rfind("outload", 0) == 0)
		{
			int l = getInt(s, "l");
			int _s = getInt(s, "s");
			int p = getInt(s, "p");
			int q = getInt(s, "q");
			Storage* st = storage(_s);
			Load* ld = load(l);
			if (st == nullptr)
				std::cout << "outload: storage " << st << " not found";
			else if (ld == nullptr)
				std::cout << "outload: load " << l << " not found";
			else
			{
				st->addOutLoad(ld, p, q);
			}
		}
	}
	file.close();
}

void Logistics::simulate(int endTime)
{
	std::cout << "todo";
}