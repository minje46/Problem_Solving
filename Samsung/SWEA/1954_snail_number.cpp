#include<iostream>
#include<algorithm>
#include<memory.h>
#pragma warning(disable:4996)
#define MAX 12

using namespace std;

int map[MAX][MAX];						// map = The memory of array map.
int N;												// N = The size of array map.

void Simulation()						// To do rotation as snail figure in array.
{
	int idx = 1, n = N;						// idx = The value.				n = The standard of array to rotate.
	int i, j, dpt = 1;							// i,j = The index of array.		dpt = Start point.

	while (n >= 1)
	{
		i = dpt;		j = dpt;					// Start point.
		
		for (int k = 0; k < n; k++)			// Go right way.
		{
			if (map[i][j + k] == 0)
				map[i][j + k] = idx++;
		}
		j = n;

		for (int k = 1; k < n; k++)			// Go down.
		{
			if (map[i + k][j] == 0)
				map[i + k][j] = idx++;
		}
		i = n;

		for (int k = 1; k < n; k++)			// Go left way.
		{
			if (map[i][j - k] == 0)
				map[i][j - k] = idx++;
		}
		j = dpt++;

		for (int k = 1; k < n - 1; k++)	// Go up.
		{
			if (map[i - k][j] == 0)
				map[i - k][j] = idx++;
		}
		n--;
	}
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);	cout.tie(0);
	
	freopen("input.txt", "r", stdin);
	int test_case;
	cin >> test_case;
	for (int t = 1; t <= test_case; t++)
	{	// Initialization.
		memset(map, 0, sizeof(map));
		cin >> N;

		Simulation();

		cout << "#" << t << endl;
		for (int i = 1; i <= N; i++)
		{
			for (int j = 1; j <= N; j++)
				cout << map[i][j] << " ";
			cout << endl;
		}
	}
}