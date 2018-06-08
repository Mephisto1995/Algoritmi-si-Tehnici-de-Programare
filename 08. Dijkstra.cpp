#include <iostream>
#include <fstream>
#pragma warning(disable:4996)
#define INFINITY 8096
#define FILE_NAME "Weighted Graph.txt"
const int source = 0;
using namespace std;

void prelucrateSize(int& size)
{
	fstream file;
	file.open(FILE_NAME, ios::in);
	if (file.is_open())
	{
		file >> size;
	}
	file.close();
}

void allocateMemory(int** &matrix, const int& size)
{
	if (matrix == nullptr)
	{
		matrix = new int*[size];
		for (int i = 0; i < size; i++)
		{
			matrix[i] = new int[size];
		}
	}
}

void infinite(int** matrix, const int& size)
{
	if (matrix != nullptr)
	{
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				matrix[i][j] == INFINITY;
			}
		}
	}
}

void road2self(int** matrix, const int& size)
{
	if (matrix != nullptr)
	{
		for (int i = 0; i < size; i++)
		{
			matrix[i][i] = 0;
		}
	}
}

void populateMatrix(int** matrix, const int& size)
{
	if (matrix != nullptr)
	{
		fstream file;
		file.open(FILE_NAME, ios::in);
		if (file.is_open())
		{
			int u, v, w;
			file.seekg(ios::beg + 1);
			while (!file.eof())
			{
				file >> u >> v >> w;
				matrix[u][v] = w;
				matrix[v][u] = w;
			}
		}
		file.close();
	}
}

int minDistance(int* dist, bool* setupSet, const int& size)
{
	int minValue = INFINITY;
	int minIndex = -1;
	if (dist != nullptr && setupSet != nullptr)
	{
		for (int i = 0; i < size; i++)
		{
			if (setupSet[i] == false && dist[i] <= minValue)
			{
				minValue = dist[i];
				minIndex = i;
			}
		}
	}
	return minIndex;
}

void displaySolution(int* dist, const int& size, const int& source)
{
	if (dist != nullptr)
	{
		cout << "Vertex Distance from source" << source << endl;
		for (int i = 0; i < size; i++)
		{
			cout << i << " to " << dist[i] << endl;
		}
	}
}

void dijkstra(int** matrix, const int& size, const int& source)
{
	if (matrix != nullptr)
	{
		int* dist = new int[size];
		bool* setupSet = new bool[size];
		for (int i = 0; i < size; i++)
		{
			dist[i] = INFINITY;
			setupSet[i] = false;
		}
		dist[source] = 0;
		for (int counter = 0; counter < size - 1; counter++)
		{
			int u = minDistance(dist, setupSet, size);
			setupSet[u] = true;
			for (int i = 0; i < size; i++)
			{
				if (setupSet[u] == false && matrix[u][i] != INFINITY &&
					dist[u] != INFINITY && matrix[u][i] + dist[u] < dist[i])
				{
					dist[i] = matrix[u][i] + dist[u];
				}
			}
		}
		displaySolution(dist, size, size);
		delete[] dist;
		delete[] setupSet;
		dist = nullptr;
		setupSet = nullptr;
	}
}

void destroyMatrix(int** matrix, const int& size)
{
	if (matrix != nullptr)
	{
		for (int i = 0; i < size; i++)
		{
			delete[] matrix[i];
			matrix[i] = nullptr;
		}
		delete[] matrix;
		matrix = nullptr;
	}
}

void main()
{
	int** matrix = nullptr;
	int size = -1;
	prelucrateSize(size);
	if (size != -1 && size > 0)
	{
		allocateMemory(matrix, size);
		infinite(matrix, size);
		road2self(matrix, size);
		populateMatrix(matrix, size);
		dijkstra(matrix, size, source);
		destroyMatrix(matrix, size);
	}
	system("pause");
}
