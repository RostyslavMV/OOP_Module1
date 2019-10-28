#include "Logistics.h"
#include "Vehicle.h"
#include <fstream>
#include <sstream>
#include <iostream>

using std::string;
using std::cout;
using std::vector;

string getVal(string s, const char* key) {
	int p1 = s.find(key, 0);
	p1 = s.find("=", p1);
	p1++;
	int p2 = s.find(";", p1);
	if (p2 == 0) p2 = s.length() - 1;
	return s.substr(p1, p2 - p1);
}

int getInt(string s, const char* key) {
	string ss = getVal(s, key);
	int ret = std::stoi(ss);
	return ret;
}

double getDbl(string s, const char* key) {
	string ss = getVal(s, key);
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
	vector<Load*>::iterator it;
	for (it = loads.begin(); it != loads.end(); it++)
	{
		if ((*it)->type == type)
			return *it;
	}
	return nullptr;
}

void Logistics::setGraph()
{
	graph.clear();
	for (int i = 0; i < storages.size(); i++)
	{
		graph.push_back(vector<double>(storages.size(), 0));
		minDistances.push_back(vector<double>(storages.size(), 0));
	}
	for (int i = 0; i < storages.size(); i++)
	{
		for (int j = 0; j < storages[i]->neighbores.size(); j++)
		{
			double distance = storages[i]->neighbores[j]->Distance();
			int index = storages[i]->neighbores[j]->Storage()->Id();
			graph[i][index] = distance;
		}
	}
}

double Logistics::minDistance(vector<double>& dist, vector<bool>& sptSet)
{
	double min = DBL_MAX, minIndex;
	for (int v = 0; v < dist.size(); v++)
		if (sptSet[v] == false && dist[v] <= min)
			min = dist[v], minIndex = v;
	return minIndex;
}

void Logistics::dijkstra()
{
	setGraph();
	for (int src = 0; src < storages.size(); src++)
	{
		vector<bool> sptSet;
		sptSet.resize(graph.size());
		for (int i = 0; i < graph.size(); i++)
			minDistances[src][i] = DBL_MAX, sptSet[i] = false;
		minDistances[src][src] = 0;
		for (int count = 0; count < graph.size() - 1; count++)
		{
			int u = minDistance(minDistances[src], sptSet);
			sptSet[u] = true;
			for (int v = 0; v < graph.size(); v++)
				if (!sptSet[v] && graph[u][v] && minDistances[src][u] != DBL_MAX
					&& minDistances[src][u] + graph[u][v] < minDistances[src][v])
					minDistances[src][v] = minDistances[src][u] + graph[u][v];
		}
	}
}


void Logistics::load(const char* fName)
{
	std::ifstream file(fName);
	string s;
	int prev = 0, pos = 0;
	while (std::getline(file, s))
	{
		if (s.rfind("storage", 0) == 0)
		{
			double x = getDbl(s, "x");
			double y = getDbl(s, "y");
			Storage* storage = new Storage(x, y);
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
				cout << "storage " << a << " not found\n";
			else if (stB == nullptr)
				cout << "storage " << b << " not found\n";
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
				cout << "inload: storage " << st << " not found\n";
			else if (ld == nullptr)
				cout << "inload: load " << l << " not found\n";
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
				cout << "outload: storage " << st << " not found\n";
			else if (ld == nullptr)
				cout << "outload: load " << l << " not found\n";
			else
			{
				st->addOutLoad(ld, p, q);
			}
		}
		else if (s.rfind("airvehicle", 0) == 0)
		{
			double v = getDbl(s, "v");
			double w = getDbl(s, "w");
			double sp = getDbl(s, "sp");
			int st = getInt(s, "st");
			int lt = getInt(s, "lt");
			int ut = getInt(s, "ut");
			Storage* str = storage(st);
			if (str == nullptr)
				cout << "outload: storage " << st << " not found\n";
			else
				vehicles.push_back(new Vehicle(v, w, sp, str, lt, ut, true));
		}
		else if (s.rfind("groundvehicle", 0) == 0)
		{
			double v = getDbl(s, "v");
			double w = getDbl(s, "w");
			int sp = getInt(s, "sp");
			int st = getInt(s, "st");
			int lt = getInt(s, "lt");
			int ut = getInt(s, "ut");
			Storage* str = storage(st);
			if (str == nullptr)
				cout << "outload: storage " << st << " not found\n";
			else
			{
				vehicles.push_back(new Vehicle(v, w, sp, str, lt, ut, false));
			}
		}
	}
	file.close();
	dijkstra();
}

void Logistics::simulate(int endTime)
{
	vector<Storage*>::iterator stIt;
	vector<PeriodicalLoad*>::iterator inloadIt;
	int time = 0;
	int nextTimeIter = endTime;
	// Ітерації
	while (nextTimeIter < endTime)
	{
		// Проходимо по всіх складах
		for (stIt = storages.begin(); stIt != storages.end(); stIt++)
		{
			Storage* st = *stIt;
			// Всі вантажі які потрібно привести
			for (inloadIt = st->inLoads.begin(); inloadIt != st->inLoads.end(); stIt++)
			{
				PeriodicalLoad* pl = *inloadIt;
				while (pl->quantity != 0)
				{
					Storage* source = priorityStorage(pl->load);
					if (source == nullptr) break; // Немає де взяти товар
					Vehicle* vehicle = priorityVehicle(st, pl->load);
					CanDeliver deliver = vehicle->request(pl->load, source, st);
					int quantity = deliver.quantity;
					if (quantity > pl->quantity)
						quantity = pl->quantity;
					vehicle->addCargo(pl->load, quantity, source, st);
				}
			}
		}
		// Визначаєм час наступної ітерації - коли треба буде везти наступний товар
				// todo
	}
}