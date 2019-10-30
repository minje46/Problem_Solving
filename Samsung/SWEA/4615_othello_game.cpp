#include<iostream>
#include<algorithm>
#include<memory.h>
#pragma warning(disable:4996)

#define MAX 10

using namespace std;

const int dy[8] = { -1,-1,-1,0,0,1,1,1 };
const int dx[8] = { -1,0,1,-1,1,-1,0,1 };

int N, M;							// N = The size of mpa.			M = The number of playing.
char map[MAX][MAX];	// map = The memory of input data.

void Init()		// To initialize the othello board based on size.
{					
	memset(map, '0', sizeof(map));
	int mid = N / 2;
	map[mid][mid] = 'W';			map[mid][mid + 1] = 'B';			// Base state.
	map[mid + 1][mid] = 'B';	map[mid + 1][mid + 1] = 'W';
}

int Count(char color)		// To count the number of blocks with color.
{
	int cnt = 0;
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			if (map[i][j] == color)		
				cnt += 1;
		}
	}
	return cnt;
}

void Convert(int y, int x, int color)		// Convert the color with (y,x,color).
{
	map[y][x] = color;		// New stone on the board.
	for (int k = 0; k < 8; k++)
	{
		bool flag = false;		// To figure out it is possible to change or not. (It has sandwich or not.)
		int ny = y, nx = x;
		while (true)
		{
			ny += dy[k];
			nx += dx[k];

			if (ny<1 || ny>N || nx<1 || nx>N)		// Overflow.
				break;

			if (map[ny][nx] == color)		// Untill finding same color.
			{
				flag = true;
				break;
			}
			if (map[ny][nx] == '0')		// Nothing.
				break;
		}

		if (flag)
		{
			int i = y, j = x;
			while (i != ny || j != nx)		// Change the color in sandwich.
			{
				map[i][j] = color;
				i += dy[k];
				j += dx[k];
			}
		}
	}
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);	cout.tie(0);

	//freopen("input.txt", "r", stdin);
	int test_case;
	cin >> test_case;
	for (int t = 1; t <= test_case; t++)
	{
		cin >> N >> M;
		Init();				// Initialization.
		for (int i = 0; i < M; i++)
		{
			int x, y, c;
			cin >> x >> y >> c;
			if (c == 1)
				Convert(y, x, 'B');		// Blcak color's turn.
			else
				Convert(y, x, 'W');		// White color's turn.
		}

		cout << "#" << t << " " << Count('B') << " " << Count('W') << endl;		// Output.
	}
}