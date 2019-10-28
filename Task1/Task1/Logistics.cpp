#include "Logistics.h"
#include <fstream>
#include <sstream>
#include <iostream>

using std::string;
using std::cout;
using std::vector;

Logistics logistic;

string getVal(std::string s, const char* key) {
	size_t p1 = s.find(key, 0);
	p1 = s.find("=", p1);
	p1++;
	size_t p2 = s.find(";", p1);
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

double Logistics::distance(Storage* a, Storage* b, bool useAir)
{
	if (useAir)
	{
		double dX = a->X() - b->X();
		double dY = a->Y() - b->Y();
		return ceil(sqrt(dX * dX + dY * dY));
	}
	else return minDistances[a->Id()][b->Id()];
}

Storage* Logistics::storage(int id)
{
	for (Storage* s : storages)
	{
		if (s->Id() == id)
			return s;
	}
	return nullptr;
}

Load* Logistics::load(int type)
{
	for (Load* l : loads)
	{
		if (l->type == type)
			return l;
	}
	return nullptr;
}

Storage* Logistics::priorityStorage(Load* load, Storage* recipient, int time)
{
	Storage* storage = nullptr;
	double dist = DBL_MAX;
	for (Storage* st : storages)
	{
		if (st->canOutload(load, time))
		{
			double d = logistic.distance(st, recipient, true);
			if (d < dist)
			{
				dist = d;
				storage = st;
			}
		}
	}
	return storage;
}

Vehicle* Logistics::priorityVehicle(Storage* sender, Storage* recipient, Load* load)
{
	int time = INT_MAX;
	Vehicle* vehicle = nullptr;
	double distAir = distance(sender, recipient, true);
	double distGround = distance(sender, recipient, false);
	for (Vehicle* v : vehicles)
	{
		DeliverRequest deliver = v->request(load, sender);
		if (deliver.quantity > 0 && deliver.time < time)
			vehicle = v;
	}
	return vehicle;
}

void Logistics::recalcVehicle(int time)
{
	for (Vehicle* v : vehicles)
		v->recalc(time);
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
	int time = 0;
	int nextTimeIter;
	// Iterations
	while (time < endTime)
	{
		// Recalculate Vehicles
		recalcVehicle(time);
		nextTimeIter = endTime;
		// Iterate through all warehouses
		for (Storage* st : storages)
		{
			int nextInLoad = st->nextInLoadTime;
			if (nextInLoad != -1)
			{ // Storage produce cargo
				if (nextInLoad == time) nextInLoad = endTime;
				// All loads we need to deliver
				for (PeriodicalLoad* pl : st->inLoads)
				{
					while (pl->quantity != 0)
					{
						Storage* source = priorityStorage(pl->load, st, time);
						if (source == nullptr) break; // Nowhere to take the loads
						Vehicle* vehicle = priorityVehicle(source, st, pl->load);
						if (!vehicle)
						{
							//cout << " no avialable vehicle: load " << pl->load->type << " from " << source->Id() << " to " << st->Id() << " qt " << pl->quantity << "\n";
							break;
						}
						double dist = distance(source, st, vehicle->isAir());
						DeliverRequest deliver = vehicle->request(pl->load, source);
						int quantity = deliver.quantity;
						if (quantity > pl->quantity)
							quantity = pl->quantity;
						vehicle->addCargo(pl->load, quantity, source, st);
						vehicle->addPath(source, st, time);
						std::cout << " time = " << time << " cargo: vehicle = " << vehicle->id << " load = " << pl->load->type << " quantity " << quantity << " from " << source->Id() << " to " << st->Id() << " path " << vehicle->path->toStr() << std::endl;
						/*cout << "*** source free " << vehicle->freeVolume(source) << "\n";
						cout << "*** dest free " << vehicle->freeVolume(st) << "\n";*/
						pl->quantity -= quantity;
					}
					// When this storage will be nearest need for cargos
					if (time + pl->nextTime < nextInLoad) nextInLoad = time + pl->nextTime;
				}
				st->nextInLoadTime = nextInLoad;
				// When for all storages will be nearest need for cargos
				if (nextTimeIter > nextInLoad)nextTimeIter = nextInLoad;
			}
		}
		time = nextTimeIter;
	}
	cout << "simulation done\n";
}

bool compareByTime(const VehicleRequest& a, const VehicleRequest& b)
{
	if (a.quantity == 0 && b.quantity > 0) return false;
	if (b.quantity == 0 && a.quantity > 0) return true;
	return a.time < b.time;
}

void Logistics::outVehicles(int storageId, int loadType, int quantity)
{
	cout << "\n ======================================================== \n";
	cout << " Vehicle list: \n\n";
	Load* l = load(loadType);
	if (l == nullptr)
	{
		cout << "loaad not found\n";
		return;
	}
	Storage* s = storage(storageId);
	if (s == nullptr)
	{
		cout << "storage not found\n";
		return;
	}
	vector<VehicleRequest> res;
	for (Vehicle* v : vehicles)
	{
		DeliverRequest request = v->request(l, s);
		VehicleRequest vr;
		vr.quantity = request.quantity;
		vr.time = request.time;
		vr.vehicle = v;
		res.push_back(vr);
	}
	sort(res.begin(), res.end(), compareByTime);
	for (VehicleRequest vr : res)
		cout << " Vehicle: " << vr.vehicle->id << " time: " << vr.time << " quantity " << vr.quantity << "\n";
}