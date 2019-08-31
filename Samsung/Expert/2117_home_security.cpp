#include<iostream>
#include<algorithm>
#include<memory.h>
#include<cmath>
//#pragma warning(disable:4996)

#define MAX 22

using namespace std;

int N, M, K;					// N = The size of map.		M = The cost to pay from each home.
int map[MAX][MAX];		// map = The memory of original map data.
bool visit[MAX][MAX];		// visit = The memory of safe area or not.
int cost[MAX];				// cost = The memory of safe security's cost.
int answer = 0;				// answer = The maximum number of home as output.

int Count()		// To count the number of home which is located in safe security.
{
	int cnt = 0;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (visit[i][j] && map[i][j] == 1)		// [visit = true] is safe area.
				cnt++;										// [map = 1] is home.
		}
	}
	return cnt;
}

void Safe_area(int y, int x, int k)		// To check the range of safe security.
{
	for (int i = 0; i < k; i++)			// Middle range.			
	{
		if (x - i >= 0)					// Not overflow.
			visit[y][x - i] = true;
		if (x + i < N)
			visit[y][x + i] = true;
	}

	for (int i = 1; i < k; i++)			// Up and Down range.
	{
		for (int j = 0; j < k - i; j++)		// Middle range.
		{
			if (y - i >= 0)		// Upper.
			{
				if (x - j >= 0)	// Left.
					visit[y - i][x - j] = true;
				if (x + j < N)	// Right.
					visit[y - i][x + j] = true;
			}
			if (y + i < N)		// Down.
			{
				if (x - j >= 0)	// Left.
					visit[y + i][x - j] = true;
				if (x + j < N)	// Right.
					visit[y + i][x + j] = true;
			}
		}
	}
}

void Simulation(int y, int x)		// To figure out the safe secrutiy from the current location.
{
	for (int i = 1; i < MAX; i++)	// Check the maximum range.
	{										// [큰 범위에서 만족하는 범위가 존재할 수 있다.]
		memset(visit, false, sizeof(visit));		// Initialization.
		Safe_area(y, x, i);			// Safe area.
		int home = Count();			// The number of home.

		if (home * M >= cost[i])	// Base case.
			answer = max(answer, home);		// Compare the number of home.
	}
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);

//	freopen("input.txt", "r", stdin);

	int test_case;
	cin >> test_case;
	for (int t = 1; t <= test_case; t++)
	{	// Initialization.
		memset(map, 0, sizeof(map));
		int cnt = 0;

		cin >> N >> M;
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				cin >> map[i][j];		// Input.
				if (map[i][j] == 1)		// Home.
					cnt++;					
			}
		}

		for (int i = 1; i < MAX; i++)	// Cost of safe security.
			cost[i] = pow(i, 2) + pow(i - 1, 2);

		answer = 0;
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
				Simulation(i, j);			// Simulation.
		}

		cout << "#" << t << " " << answer << endl;		// Output.
	}
}