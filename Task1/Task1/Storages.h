#pragma once
#include <vector>
#include "Storage.h"

using std::vector;

class Storages
{
private:
	vector<vector<double>> roadsLengths;
	vector<vector<double>> graph;
	void setGraph()
	{
		for (int i = 0; i < storages.size(); i++)
		{
			graph.push_back(vector<double>(storages.size() - 1, 0));
		}
		for (int i = 0; i < storages.size(); i++)
		{
			graph.push_back(vector<double>(storages.size() - 1, 0));
			for (int j = 0; j < storages[i]->neighboringStorages.size(); j++)
			{
				double distance = storages[i]->neighboringStorages[j].distance;
				int index = storages[i]->neighboringStorages[j].storage->id;
				graph[i][index] = distance;
			}
		}
	}
	double minDistance(vector<double> dist, vector<bool> sptSet)
	{
		int min = DBL_MAX, min_index = 0;
		for (int v = 0; v < storages.size(); v++)
		{
			if (sptSet[v] == false && dist[v] <= min)
				min = dist[v], min_index = v;
		}
		return min_index;
	}
public:
	vector<Storage*> storages;
	double GetRoadLength(Storage* start, Storage* destination)
	{
		return roadsLengths[start->id][destination->id];
	}
	//Dijkstra’s shortest path algorithm
	void CalculateRoadLengthes()
	{
		roadsLengths.resize(storages.size());
		for (int src = 0; src < storages.size(); src++)
		{
			vector<bool> sptSet;
			sptSet.resize(storages.size());

			for (int i = 0; i < storages.size(); i++)
				roadsLengths[src][i] = DBL_MAX, sptSet[i] = false;

			roadsLengths[src][src] = 0;

			for (int count = 0; count < storages.size() - 1; count++)
			{

				int u = minDistance(roadsLengths[src], sptSet);

				sptSet[u] = true;
				for (int v = 0; v < storages.size(); v++)
				{
					if (!sptSet[v] && graph[u][v] && roadsLengths[src][u] != DBL_MAX
						&& roadsLengths[src][u] + graph[u][v] < roadsLengths[src][v])
					{
						roadsLengths[src][v] = roadsLengths[src][u] + graph[u][v];
					}
				}
			}
		}
	}
	Storages(vector<Storage*>& storages)
	{
		this->storages = storages;
		for (int i = 0; i < storages.size(); i++)
		{
			storages[i]->id = i;
		}
		setGraph();
	}
	friend class GroundVehicle;
};

