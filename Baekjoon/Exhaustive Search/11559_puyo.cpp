#include<iostream>
#include<algorithm>
#include<memory.h>
#include<vector>
#include<stack>

#define HEIGHT 12
#define WIDTH 6

using namespace std;

const int dy[4] = { -1,1,0,0 };
const int dx[4] = { 0,0,-1,1 };

char map[HEIGHT][WIDTH];		// map = The memory of original input data.	
int visit[HEIGHT][WIDTH];			// visit = The memory of visited or not.
vector<pair<int, int>> puyo;			// puyo = The memory of same colors block.
int answer = 0;							// answer = The number of crushed as output.

bool Check()		// To figure out whether it has puyo more or not.
{
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			if (visit[i][j] == 1)		// The condition of puyo.
				return false;
		}
	}
	return true;
}

void Drop()			// To drop the crushed block to downside.
{
	for (int j = 0; j < WIDTH; j++)
	{
		stack<char>stk;		// Temporary memory for drop.
		for (int i = 0; i < HEIGHT; i++)
		{
			if (map[i][j] != '.')		
			{
				stk.push(map[i][j]);
				map[i][j] = '.';
			}
		}

		int k = HEIGHT;			// Switch the block from downside.
		while (!stk.empty())
		 {
			map[--k][j] = stk.top();
			stk.pop();
		}
	}
}

void Crush()		// To do puyo puyo.
{
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			if (visit[i][j] == 1)		// The condition of puyo.
				map[i][j] = '.';
		}
	}
}

void DFS(int y, int x, int color)		// To figure out the same color blocks.
{
	visit[y][x] = 1;		// visit check.
	puyo.push_back(make_pair(y, x));
	for (int i = 0; i < 4; i++)
	{
		int ny = y + dy[i];
		int nx = x + dx[i];

		if (ny < 0 || ny >= HEIGHT || nx < 0 || nx >= WIDTH)		// Overflow.
			continue;

		if (visit[ny][nx] == 0 && map[ny][nx] == color)		// Not visited yet + Same color.
			DFS(ny, nx, color);
	}
}

void Simulation()			// Puyo puyo.
{
	while (true)
	{
		memset(visit, 0, sizeof(visit));		// Initialization.
		for (int i = 0; i < HEIGHT; i++)
		{
			for (int j = 0; j < WIDTH; j++)
			{
				if (visit[i][j] == 0 && map[i][j] != '.')		// Not visited yet + Not empty zone.
				{
					puyo.clear();					// Initialization.
					DFS(i, j, map[i][j]);		// DFS algorithm to find same color blocks.

					if (puyo.size() >= 4)			// Possible to puyo.
					{
						for (int r = 0; r < puyo.size(); r++)
							visit[puyo[r].first][puyo[r].second] = 1;		// [visit = 1] is possible to puyo.
					}
					else								// Impossible to puyo.
					{
						for (int r = 0; r < puyo.size(); r++)
							visit[puyo[r].first][puyo[r].second] = -1;		// [visit = 1] is impossible to puyo.
					}
				}
			}
		}
		Crush();			// If there is puyo, do crush.
		Drop();			// If there is extra blocks, do drop. 

		if (Check())		// If tehre is no more do puyo,
			break;		// break.
		answer++;
	}
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
			cin >> map[i][j];				// Input.
	}

	Simulation();		// Puyo Puyo.

	cout << answer << endl;				// Output.
}