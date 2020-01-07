#include<iostream>
#include<algorithm>
#include<memory.h>
#pragma warning(disable:4996)
#define MAX 10

using namespace std;

int map[MAX][MAX];					// map = The memory of sudoku map.
bool visit[MAX];							// visit = The memory of 1~9 numbers are visited or not.

bool Square()			// To figure out square format has correct form of sudoku.
{
	for (int i = 1; i < MAX; i += 3)
	{
		for (int j = 1; j < MAX; j += 3)
		{
			memset(visit, false, sizeof(visit));			// Initialization.
			for (int k = 0; k < 3; k++)
			{
				if (!visit[map[i + k][j + k]])				// 1~9 numbers not visited yet.
					visit[map[i + k][j + k]] = true;
				else												// Already visited.	
					return false;
			}
		}
	}
}

bool Column()		// To figure out each column has correct form of sudoku.
{
	for (int j = 1; j < MAX; j++)
	{
		memset(visit, false, sizeof(visit));			// Initialization.
		for (int i = 1; i < MAX; i++)
		{
			if (!visit[map[i][j]])							// 1~9 numbers not visited yet.
				visit[map[i][j]] = true;
			else												// Already visited.	
				return false;
		}
	}
}

bool Row()				// To figure out each row has correct form of sudoku.
{
	for (int i = 1; i < MAX; i++)
	{
		memset(visit, false, sizeof(visit));			// Initialization.
		for (int j = 1; j < MAX; j++)
		{
			if (!visit[map[i][j]])							// 1~9 numbers not visited yet.
				visit[map[i][j]] = true;
			else												// Already visited.	
				return false;
		}
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
	{
		for (int i = 1; i < MAX; i++)
		{
			for (int j = 1; j < MAX; j++)
				cin >> map[i][j];
		}

		if (Row() && Column() && Square())
			cout << "#" << t << " " << 1 << endl;
		else
			cout << "#" << t << " " << 0 << endl;
	}
}