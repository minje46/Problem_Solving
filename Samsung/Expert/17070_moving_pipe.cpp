#include<iostream>
#include<algorithm>
#include<memory.h>
#include<vector>

#define MAX 17

using namespace std;

const int pipe[4][2] = {		// The three types of pipe.
	{0,0}, {0,1}, {1,0}, {1,1}	// Type 1 : Move to right.		Type 2 : Move to down.		Type 3 : Move to diagonal.
};

int N;			// N = The size of map.
int map[MAX][MAX];			// map = The memory of original map data.
int answer = 0;			// answer = The number of possible cases.

bool Range(int y, int x)			// To check (y,x) is included in possible range or overflow.
{
	if (y < 1 || y>N || x <1 || x>N)		// Overflow.
		return false;

	return true;
}

void DFS(int y, int x, int idx)		// To do dfs from (y,x) to (N,N) with type of pipe.
{
	if (y == N && x == N)		// Base case. [Destination.]
	{
		answer++;		// Increase the possible case.
		return;
	}

	switch (idx)		// Depends on pipe type.
	{
	case 1:		// Move to right.
	{
		if (map[y][x + 1] == 0 && Range(y, x+1))		// Type 1.
			DFS(y, x + 1, idx);			// Need only right space.

		bool flag = true;		// To check type 3 is possible or not.
		for (int i = 1; i <= 3; i++)		// Type 3.
		{										// Need 3 spaces.
			if (map[y + pipe[i][0]][x + pipe[i][1]] != 0 || !Range(y + pipe[i][0], x + pipe[i][1]))
			{
				flag = false;
				break;
			}
		}
		if (flag)
			DFS(y + 1, x + 1, 3);
		break;
	}

	case 2:		// Move to down.
	{
		if (map[y + 1][x] == 0 && Range(y + 1, x))	// Type 2.
			DFS(y + 1, x, idx);			// Need only right space.

		bool flag = true;		// To check type 3 is possible or not.
		for (int i = 1; i <= 3; i++)		// Type 3.
		{										// Need 3 spaces.
			if (map[y + pipe[i][0]][x + pipe[i][1]] != 0 || !Range(y + pipe[i][0], x + pipe[i][1]))
			{
				flag = false;
				break;
			}
		}
		if (flag)
			DFS(y + 1, x + 1, 3);
		break;
	}

	case 3:		// Move to diagonal.
	{
		if (map[y][x + 1] == 0 && Range(y, x + 1))		// Type 1.
			DFS(y, x + 1, 1);			// Need only right space.

		if (map[y + 1][x] == 0 && Range(y + 1, x))	// Type 2.
			DFS(y + 1, x, 2); 		// Need only right space.

		bool flag = true;		// To check type 3 is possible or not.
		for (int i = 1; i <= 3; i++)		// Type 3.
		{										// Need 3 spaces.
			if (map[y + pipe[i][0]][x + pipe[i][1]] != 0 || !Range(y + pipe[i][0], x + pipe[i][1]))
			{
				flag = false;
				break;
			}
		}
		if (flag)
			DFS(y + 1, x + 1, 3);
		break;
	}

	default:
		break;
	}
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> N;
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
			cin >> map[i][j];		// Original map data.
	}

	DFS(1, 2, 1);		// The basic state has one pipe is type 1 on (1,1)~(1,2).

	cout << answer << endl;		// The total number of possible cases.
}