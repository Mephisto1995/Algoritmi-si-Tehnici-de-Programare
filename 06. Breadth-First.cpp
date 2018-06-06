#include <iostream>
#include <fstream>
#include <queue>
#include <chrono>
#pragma warning(disable:4996)
using namespace std;
#define FILE_NAME "Breadth-First.txt"

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

void zeroMatrix(int** matrix, const int& size)
{
	if (matrix != nullptr)
	{
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				matrix[i][j] = 0;
			}
		}
	}
}

void populateMatrix(int** matrix)
{
	fstream file;
	file.open(FILE_NAME, ios::in);
	if (file.is_open())
	{
		// Avoid adding the size variable;
		file.seekg(ios::beg + 1);
		int u, v;
		while (!file.eof())
		{
			file >> u >> v;
			matrix[u][v] = 1;
			matrix[v][u] = 1;
		}
	}
	file.close();
}

void displayMatrix(int** matrix, const int& size)
{
	cout << "--------------------------------DISPLAY MATRIX--------------------------------" << endl;
	if (matrix != nullptr)
	{
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				cout << "matrix[" << i << "][" << j << "]: " << matrix[i][j] << endl;
			}
			cout << endl;
		}
	}
}

void breadth_first(int** matrix, const int& size)
{
	queue<int> queue;
	int node;
	int* visited = new int[size];
	for (int i = 0; i < size; i++)
	{
		visited[i] = 0;
	}
	if (matrix != nullptr)
	{
		// DISCLAIMER: I know that it would've been easier to just simply write:
		//node = matrix[0][0];

		// Add the first element of the matrix to the queue;
		queue.push(matrix[0][0]);

		// Put that value in node;
		node = queue.front();

		// Mark the first element as visited;
		visited[0] = 1;

		// Print the removed node;
		cout << "Node removed from queue: " << node << endl;

		// Remove it from queue;
		queue.pop();
		while (true)
		{
			for (int i = 0; i < size; i++)
			{
				// Check if route exists and that node isn't visited;
				if (matrix[node][i] == 1 && visited[i] == 0)
				{
					// Visit node
					visited[i] = 1;

					// Enqueue element;
					queue.push(i);
				}
			}

			// When queue is empty, break;
			if (queue.size() == 0)
			{
				break;
			}
			else
			{
				// Put new value in node, the first element inserted is the first to be removed (FIFO principle)
				node = queue.front();

				// Print the future to be removed node;
				cout << "Node removed from queue: " << node << endl;

				// Actually remove node;
				queue.pop();
			}
		}
	}
}

void main()
{
	int** matrix = nullptr;
	int size = -1;
	prelucrateSize(size);
	if (size != -1)
	{
		allocateMemory(matrix, size);
		zeroMatrix(matrix, size);
		populateMatrix(matrix);
		displayMatrix(matrix, size);
		breadth_first(matrix, size);
	}
	system("pause");
}
