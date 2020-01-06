#include<iostream>
#include<algorithm>
#include<memory.h>
#pragma warning(disable:4996)
#define MAX 11

using namespace std;

int map[MAX][MAX];						// map = The memory of array map.
int N;												// N = The size of array map.

void Simulation()						// To do rotation as snail figure in array.
{
	int idx = 1, n = N;						// idx = The value.								n = The standard of array to rotate.
	int i = 0, j = -1, dir = 1;				// i,j = The row and column of array.		dir = On going direction.

	while (n > 0)
	{
		for (int k = 0; k < n; k++)				// Columns.
		{
			j += dir;
			map[i][j] = idx++;
		}
		n--;
		
		for (int k = 0; k < n; k++)				// Rows.
		{
			i += dir;
			map[i][j] = idx++;
		}
		dir *= -1;									// Control increse and decrease with direction way.
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
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
				cout << map[i][j] << " ";
			cout << endl;
		}
	}
}