#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;
#define INF 0x3f3f3f3f

struct edge {
	int vertice1;
	int vertice2;
	int cost;
};
struct pereche {
	int cost;
	int nod;
};
struct myComparator {
	bool operator() (const pereche& i1, const pereche& i2) {
		return (i1.cost > i2.cost);
	}
};


vector<int> dijkstra(vector<edge> edges, int source, int n) {
	priority_queue<pereche, vector<pereche>, myComparator> pq;
	vector<int> dist;
	int *cost = new int[n];
	for (int i = 0; i < n; i++) {
		cost[i] = INF;
	}
	cost[source - 1] = 0;
	pereche sourcePair;
	sourcePair.cost = cost[source - 1];
	sourcePair.nod = source;
	pq.push(sourcePair);
	while (!pq.empty()) {
		int node = pq.top().nod;
		pq.pop();
		for (int i = 0; i < edges.size(); i++) {
			if (edges[i].vertice1 == node) {
				if (cost[edges[i].vertice2 - 1] > cost[node - 1] + edges[i].cost) {
					cost[edges[i].vertice2 - 1] = cost[node - 1] + edges[i].cost;
					pereche newPair;
					newPair.cost = cost[edges[i].vertice2 - 1];
					newPair.nod = edges[i].vertice2;
					pq.push(newPair);
				}
			}
		}
	}
	for (int i = 0; i < n; i++) {
		dist.push_back(cost[i]);
	}
	delete[] cost;
	return dist;
}

int main() {
	vector<edge> edges;
	edge edge1;
	edge1.vertice1 = 1;
	edge1.vertice2 = 2;
	edge1.cost = 10;
	edges.push_back(edge1);
	edge edge2;
	edge2.vertice1 = 1;
	edge2.vertice2 = 3;
	edge2.cost = 50;
	edges.push_back(edge2);
	edge edge3;
	edge3.vertice1 = 1;
	edge3.vertice2 = 4;
	edge3.cost = 30;
	edges.push_back(edge3);
	edge edge4;
	edge4.vertice1 = 2;
	edge4.vertice2 = 3;
	edge4.cost = 20;
	edges.push_back(edge4);
	edge edge5;
	edge5.vertice1 = 3;
	edge5.vertice2 = 5;
	edge5.cost = 10;
	edges.push_back(edge5);
	edge edge6;
	edge6.vertice1 = 4;
	edge6.vertice2 = 5;
	edge6.cost = 10;
	edges.push_back(edge6);
	vector<int> dist;
	dist = dijkstra(edges, 1, 5);
	for(int i = 0; i < dist.size(); i++)
	{
		cout << "Distanta intre nodul sursa 1 si nodul " << i + 1 << " este: " << dist[i] << endl;
	}
	system("Pause");
}