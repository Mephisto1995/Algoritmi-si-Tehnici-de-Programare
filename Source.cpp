#include <iostream>
#include <fstream>
#pragma warning(disable:4996)
#define file_name "Floyd Warshall.txt"
#define INFINITY 8096
#define pause "pause"
using namespace std;

void prelucrateSize(int& size)
{
	fstream file;
	file.open(file_name, ios::in);
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

void infinity(int** matrix, const int& size)
{
	if (matrix != nullptr)
	{
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				matrix[i][j] = INFINITY;
			}
		}
	}
}

void prelucrateMatrix(int** matrix)
{
	if (matrix != nullptr)
	{
		fstream file;
		file.open(file_name, ios::in);
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

void displayMatrix(int** matrix, const int& size)
{
	cout << "-----------------------------------DISPLAY MATRIX-----------------------------------" << endl;
	if (matrix != nullptr)
	{
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				if (matrix[i][j] == INFINITY)
				{
					cout << "matrix[" << i << "][" << j << "]: INFINITY" << endl;
				}
				else
				{
					cout << "matrix[" << i << "][" << j << "]: " << matrix[i][j] << endl;
				}
			}
			cout << endl;
		}
	}
}

void floyd_warshall(int** matrix, const int& size)
{
	if (matrix != nullptr)
	{
		for (int k = 0; k < size; k++)
		{
			for (int i = 0; i < size; i++)
			{
				for (int j = 0; j < size; j++)
				{
					if (matrix[i][j] > matrix[i][k] + matrix[k][j])
					{
						matrix[i][j] = matrix[i][k] + matrix[k][j];
					}
				}
			}
		}
	}
}

void destroy(int** &matrix, const int& size)
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
	if (size > -1 && size != 0)
	{
		allocateMemory(matrix, size);
		infinity(matrix, size);
		prelucrateMatrix(matrix);
		displayMatrix(matrix, size);
		floyd_warshall(matrix, size);
		displayMatrix(matrix, size);
		destroy(matrix, size);
	}
	system(pause);
}