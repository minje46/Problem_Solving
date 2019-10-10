#include<iostream>
#include<memory.h>

#define MAX 12

using namespace std;

const int dy[4] = { -1,1,0,0 };
const int dx[4] = { 0,0,-1,1 };

int N, M;										// N = The height of map.				M = The width of map.
char map[MAX][MAX][MAX];		// map = The memory of input data.
int answer = 0;							// answer = Whether it is possible to escape or not as output.

bool Check(int prev, int cur)			// To check whether it is possible to move or not.
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
			if (map[prev][i][j] != map[cur][i][j])		// Not exactly same.
				return false;										// means beads were moved.			
	}
	return true;
}

void Copy(int dpt, int dst)			// To copy the current map to next map.
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
			map[dst][i][j] = map[dpt][i][j];
	}
}

bool Move(int idx, int dir)			// To roll the beads based on simulation.
{
	pair<int, int> ball[2];			// ball[0] : Red, ball[1] : Blue.
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			if (map[idx][i][j] == 'R' || map[idx][i][j] == 'B')		// Beads.
			{
				if (map[idx][i][j] == 'R')		// Red.
					ball[0] = { i,j };
				else									// Blue.
					ball[1] = { i,j };
				map[idx][i][j] = '.';			// Treat as empty.
			}
		}
	}

	int fir = 0, sec = 1;		// Base case.
	if (dir == 0)		// Up.
	{
		if (ball[0].first - ball[1].first > 0)		// Blue ball is upper than red ball.
		{
			fir = 1;		// Roll the blue one first.
			sec = 0;
		}
	}
	else if (dir == 1)		// Down.
	{
		if (ball[0].first - ball[1].first < 0)		// Blue ball is downside than red ball.
		{
			fir = 1;		// Roll the blue one first.
			sec = 0;
		}
	}
	else if (dir == 2)
	{
		if (ball[0].second - ball[1].second > 0)		// Blue ball is left side than red ball.
		{
			fir = 1;		// Roll the blue one first.
			sec = 0;
		}
	}
	else if (dir == 3)
	{
		if (ball[0].second - ball[1].second < 0)		// Blue ball is right side than red ball.
		{
			fir = 1;		// Roll the blue one first.
			sec = 0;
		}
	}

	bool hole[2] = { false, false };		// Ball is in the hole or not.
	for (int r = 0; r < 2; r++)		// Red and Blue, two balls.
	{
		pair<int, int>p;
		if (r == 0)			// First one to move earlier.
			p = ball[fir];
		else					// Next one.
			p = ball[sec];

		int y = p.first, x = p.second;
		while (map[idx][y][x] == '.')		// Ball could roll in only empty space.
		{
			y += dy[dir];
			x += dx[dir];
		}

		if (map[idx][y][x] == 'O')		// If the ball arrives at hole,
		{
			if (r == 0)		// The first rolled ball. 
				hole[fir] = true;	
			else				// The second one.
				hole[sec] = true;
		}
		else		// Other cases : Arrive at '#'(wall) or another ball.
		{			// return to previous location arrived.
			y -= dy[dir];
			x -= dx[dir];
			
			if (r == 0)		// If the first rolled ball is,
			{
				if (fir == 0)	// Red one.
					map[idx][y][x] = 'R';
				else
					map[idx][y][x] = 'B';
			}
			else				// If the second rolled ball is
			{
				if (sec == 1)	// Blue one.
					map[idx][y][x] = 'B';
				else
					map[idx][y][x] = 'R';
			}
		}
	}

	if (hole[0] == false && hole[1] == false)		// Both balls are on the map,
		return true;												// it could roll continuously.
	else		// If not, it should be stopped.
	{
		if (hole[0] == true && hole[1] == false)		// Success case.
			answer = 1;
		return false;
	}
}

void DFS(int idx)		// To figure out whether it is possible to finish bead escape based on dfs.
{
	if (answer)		// Base case. [It doesn't need to take care any more.]
		return;

	if (idx >= 10)	// Base case2. [The criteria for exit.]
	{
		answer = 0;
		return;
	}

	for (int i = 0; i < 4; i++)
	{
		if (idx > 0)	// Except the first case.
		{
			if (Check(idx - 1, idx))		// To check it has chage or not.
				return;
		}
		Copy(idx, idx + 1);		// To copy the previous map data to new map data.
		if (Move(idx + 1, i))		// Roll the balls.
			DFS(idx + 1);			// DFS algorithm.
	}
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);	cout.tie(0);

	cin >> N >> M;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
			cin >> map[0][i][j];		// Input map data.
	}

	DFS(0);		// DFS algorithm.

	cout << answer << endl;		// Output.
}