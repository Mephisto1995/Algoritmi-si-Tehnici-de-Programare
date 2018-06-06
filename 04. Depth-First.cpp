#include <iostream>
#include <fstream>
#include <stack>
#include <chrono>
#pragma warning(disable:4996)
using namespace std;
#define FILE_NAME "Depth-First.txt"

void prelucrateSize(int& size)
{
	cout << "prelucrateSize()" << endl;
	fstream file;
	file.open(FILE_NAME, ios::in);
	if (file.is_open())
	{
		file >> size;
		file.close();
	}
	else
	{
		cout << "prelucrateSize: ERROR on opening file: " << FILE_NAME;
	}
}

void allocateMemory(int** &matrix, const int& size)
{
	cout << "allocateMemory()" << endl;
	if (matrix == nullptr)
	{
		matrix = new int*[size];
		for (int i = 0; i < size; i++)
		{
			matrix[i] = new int[size];
		}
	}
	else
	{
		cout << "allocateMemory: ERROR matrix is NOT nullptr!" << endl;
	}
}

void zeroMatrix(int** matrix, const int& size)
{
	cout << "zeroMatrix()" << endl;
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
	else
	{
		cout << "zeroMatrix: ERROR matrix IS nullptr!" << endl;
	}
}

void displayMatrix(int** matrix, const int& size)
{
	cout << "-----------------------------DISPLAY MATRIX-----------------------------" << endl;
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
	else
	{
		cout << "displayMatrix: ERROR matrix IS nullptr!" << endl;
	}
}

void populateMatrix(int** matrix)
{
	cout << "populateMatrix()" << endl;
	fstream file;
	file.open(FILE_NAME, ios::in);
	int u, v;
	if (file.is_open())
	{
		file.seekg(ios::beg + 1);
		while (!file.eof())
		{
			file >> u >> v;
			matrix[u][v] = 1;
			matrix[v][u] = 1;
		}
		file.close();
	}
	else
	{
		cout << "populateMatrix: ERROR on opening file: " << FILE_NAME << endl;
	}
}

void depth_first(int** matrix, const int& size)
{
	cout << "-----------------------------DEPTH FIRST TRAVERSAL ALGORITHM-----------------------------" << endl;
	stack<int> stack;
	int node;
	int* visited = new int[size];
	for (int i = 0; i < size; i++)
	{
		visited[i] = 0;
	}
	if (matrix != nullptr)
	{
		// Add the first node to the stack 
		stack.push(matrix[0][0]);

		// Visited value of first node is set to 1, since it was visited
		visited[0] = 1;

		// Pop the stack and display the removed node from stack
		node = stack.top();
		cout << "Node removed from stack: " << node << endl;
		stack.pop();

		while (true)
		{
			// Iterate over all nodes
			for (int i = 0; i < size; i++)
			{
				// Check if the route exists and that node isn't visited
				if (matrix[node][i] == 1 && visited[i] == 0)
				{
					// Visit the node
					visited[i] = 1;

					// Push the element to the stack
					stack.push(i);
				}
			}

			// When stack is empty, break
			if (stack.size() == 0)
			{
				break;
			}
			else
			{
				// Pop the element from the stack
				node = stack.top();
				cout << "Node removed from stack: " << node << endl;

				// Removes element from stack which was displayed;
				stack.pop();
			}
		}
	}
	else
	{
		cout << "depth_first: ERROR matrix IS nullptr" << endl;
	}
	delete[] visited;
	visited = nullptr;
}

void destroyMatrix(int** &matrix, const int& size)
{
	if (matrix != nullptr)
	{
		int** temp = matrix;
		for (int i = 0; i < size; i++)
		{
			delete[] temp[i];
			temp[i] = nullptr;
		}
		delete[] temp;
		temp = nullptr;
		matrix = temp;
	}
	else
	{
		cout << "destroyMatrix: ERROR matrix IS nullptr" << endl;
	}
}

void main()
{
	auto start = chrono::steady_clock::now();
	int** matrix = nullptr;
	int size = -1;
	prelucrateSize(size);
	if (size != -1)
	{
		allocateMemory(matrix, size);
		zeroMatrix(matrix, size);
		populateMatrix(matrix);
		displayMatrix(matrix, size);
		depth_first(matrix, size);
		destroyMatrix(matrix, size);
	}
	auto end = chrono::steady_clock::now();
	cout << "Program executed successfully in " << chrono::duration<double, milli>(end - start).count() << "ms!" << endl;
	system("pause");
}