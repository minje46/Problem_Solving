#include<iostream>
#include<memory.h>
#include<vector>
#include<queue>

#define MAX 51

using namespace std;

const int dy[8] = { -1,-1,-1,0,1,1,1,0 };
const int dx[8] = { -1,0,1,1,1,0,-1,-1 };
const int VH[2][3][2] = { {{-1,0},{0,0},{1,0}},{{0,-1},{0,0},{0,1}} };		// The range of Vertical(0) and Horizontal(1) figure's tree.

struct location		// The data of location.
{
	int y, x;			// The central of log location.
	int fig;			// Figure. [0 : Vertical] [1 : Horizaontal]
	int cnt;			// The number of movement.
};

int N;										// N = The size of map.
char map[MAX][MAX];			// map = The memory of input data.
bool visit[2][MAX][MAX];		// visit = The memory of visited or not.

bool Promising(int y, int x)	// To check it is correct location or not.
{
	if (y < 0 || y >= N || x < 0 || x >= N || map[y][x] == '1')	// Overflow or Tree zone.
		return false;
	return true;
}

bool Arrive(location cur)		// To figure out it arrives at destination or not.
{
	for (int i = 0; i < 3; i++)	// The size of tree log. [Default : 3]
	{
		int ny = cur.y + VH[cur.fig][i][0];		// VH[0] : Vertical.	
		int nx = cur.x + VH[cur.fig][i][1];		// VH[1] : Horizaontal.

		if (map[ny][nx] != 'E')		// Destination.
			return false;
	}
	return true;
}

struct location Simulation(location cur, int dir)			// To change the log's figure.
{
	int y = cur.y;
	int x = cur.x;
	if (dir == 0)		// 'Up'
	{	// Organize the coordinate as (y-1).
		y += VH[0][0][0];
		x += VH[0][0][1];
	}
	else if (dir == 1)		// 'Down'
	{	// Organize the coordinate as (y+1).
		y += VH[0][2][0];
		x += VH[0][2][1];
	}
	else if (dir == 2)		// 'Left'
	{	// Organize the coordinate as (x-1).
		y += VH[1][0][0];
		x += VH[1][0][1];
	}
	else if (dir == 3)		// 'Right'
	{	// Organize the coordinate as (x+1).
		y += VH[1][2][0];
		x += VH[1][2][1];
	}

	bool flag = true;		// Possible or not.
	if (dir < 4)		// Moving log.
	{
		for (int i = 0; i < 3; i++)
		{
			int ny = y + VH[cur.fig][i][0];
			int nx = x + VH[cur.fig][i][1];

			if (!Promising(ny, nx))		// To check promising or not.
			{
				flag = false;
				break;
			}
		}
	}
	else			// Turn log.
	{
		for (int i = 0; i < 8; i++)
		{
			int ny = y + dy[i];
			int nx = x + dx[i];

			if (!Promising(ny, nx))		// To check promising or not.
			{
				flag = false;
				break;
			}
		}
	}

	if (flag)		// Possible to move.
	{
		if (dir == 0)				// 'Up'
			cur.y -= 1;
		else if (dir == 1)		// 'Down'
			cur.y += 1;
		else if (dir == 2)		// 'Left'
			cur.x -= 1;
		else if (dir == 3)		// 'Right'
			cur.x += 1;
		else						// 'Turn'
		{
			if (cur.fig == 0)	// From Vertical.
				cur.fig = 1;		// To Horizon.
			else					// From Horizon.
				cur.fig = 0;		// To Vertical.
		}
	}

	return cur;
}

int BFS(int y, int x, char fig)		// To figure out the shortest way to arrive at destination.
{	// Initialization.
	memset(visit, false, sizeof(visit));
	visit[fig][y][x] = true;

	queue<location>que;
	que.push({ y,x,fig,0 });		// Base case.
	while (!que.empty())
	{
		auto cur = que.front();
		que.pop();

		if (Arrive(cur))			// Base case. [Arrive at destination or not.]
			return cur.cnt;		// Shortest way to arrive at.

		for (int i = 0; i < 5; i++)
		{
			location nxt = Simulation(cur, i);		// Move the log or Turn the log.
			if (nxt.y != cur.y || nxt.x != cur.x || nxt.fig != cur.fig)		// If there is any change, it could be moved.
			{
				if (!visit[nxt.fig][nxt.y][nxt.x])		// Not visit yet with current figure.
				{
					nxt.cnt += 1;		
					que.push(nxt);
					visit[nxt.fig][nxt.y][nxt.x] = true;
				}
			}
		}
	}
	return -1;
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);	cout.tie(0);

	vector<pair<int, int>> dpt;	// dpt = The location of departure.
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> map[i][j];		// Input data.
			if (map[i][j] == 'B')		// Departure. (Tree log location.)
			{
				dpt.push_back(make_pair(i, j));
				map[i][j] == '0';		// Make as empty.
			}
		}
	}

	int fig = 0;		// Vertical.
	if (dpt[0].first == dpt[1].first)	// Same y coordinate.
		fig = 1;		// Horizontal.


	int answer = BFS(dpt[1].first, dpt[1].second, fig);		// BFS algorithm.
	if (answer == -1)			// Impossible case.
		answer = 0;
	cout << answer << endl;			// Output.
}