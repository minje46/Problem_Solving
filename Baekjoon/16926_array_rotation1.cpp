#include<iostream>
#include<algorithm>
#include<memory.h>

#define MAX 51
#define INF 987654321

using namespace std;

int N, M;					// N = The height of map.			M = The width of map.
char map[MAX][MAX], tmp[MAX][MAX];		// map = The memory of original input.
int answer = INF;		// answer = The minimum number of repaint as output.

void Copied(int y, int x)		// To copy the original map data to temporary memory.
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
			tmp[i][j] = map[y + i][x + j];
	}
}

void Simulation(char a, char b)			// To figure out the chess board's figure.
{
	int cnt = 0;		// Count the number of painted.
	char color[2] = { a,b };		// The basic colors set.

	for (int i = 0; i < 8; i++)
	{
		if (i != 0)	// Each row has different color set.
			swap(color[0], color[1]);
		for (int j = 0; j < 8; j++)
		{
			if (j % 2 == 0)		// Each column has opposite color.
			{
				if (tmp[i][j] != color[0])		// Every even column has same color.
				{
					tmp[i][j] = color[0];
					cnt += 1;
				}
			}
			else
			{
				if (tmp[i][j] == color[0])		// Every odd column has same color.
				{
					tmp[i][j] = color[1];
					cnt += 1;
				}
			}
		}
	}
	answer = min(answer, cnt);			// Compare the minimum number of painted.
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> N >> M;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
			cin >> map[i][j];				// Input.
	}

	for (int i = 0; i <= N - 8; i++)
	{
		for (int j = 0; j <= M - 8; j++)
		{
			Copied(i, j);					// Temporary memory.
			Simulation('B', 'W');		// Paint to ['B', 'W'] chess board.	
			Copied(i, j);					// Temporary memory.
			Simulation('W', 'B');		// Paint to ['W', 'B'] chess board.
		}
	}

	cout << answer << endl;				// Output.
}