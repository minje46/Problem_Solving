#include<iostream>
#include<algorithm>
#include<memory.h>
#include<queue>

#define MAX 51

using namespace std;

const int dy[4] = { 0,-1,0,1 };
const int dx[4] = { -1,0,1,0 };

struct Wall			// The data of wall.
{
	bool dir[4];	// [0 : West] [1 : North] [2 : East] [3 : South]
};

int N, M;							// N = The hieght of map.			M = The width of map.
Wall map[MAX][MAX];	// map = The memory of 	input data. (The wall state.)
bool visit[MAX][MAX];		// visit = The memory of visited or not.
int area[MAX*MAX];		// area = The memory of each area's size.
int answer = 0;				// answer = The biggest size of combined rooms.

void Binary(int y, int x, int val)		// To check where the wall is.
{
	if (val == 0)	// No wall.	
	{
		for (int i = 0; i < 4; i++)
			map[y][x].dir[i] = false;
		return;
	}

	while (val > 0)	
	{
		if (val >= 8)	// South.	
		{
			map[y][x].dir[3] = true;
			val -= 8;
		}
		else if (val >= 4)		// East.
		{
			map[y][x].dir[2] = true;
			val -= 4;
		}
		else if (val >= 2)		// North. 
		{
			map[y][x].dir[1] = true;
			val -= 2;
		}
		else if (val >= 1)		// West.
		{
			map[y][x].dir[0] = true;
			val -= 1;
		}
	}
}

int BFS(int y, int x)		// To figure out the movement.
{
	int cnt = 1;		// The size of area.
	queue<pair<int, int>> que;
	que.push(make_pair(y, x));
	visit[y][x] = true;
	while (!que.empty())
	{
		auto cur = que.front();
		que.pop();

		for (int i = 0; i < 4; i++)
		{
			int ny = cur.first + dy[i];
			int nx = cur.second + dx[i];

			if (ny < 0 || ny >= N || nx < 0 || nx >= M || visit[ny][nx])		// Over flow. + Visited.
				continue;
			
			int ops = (i + 2) % 4;
			if (!map[cur.first][cur.second].dir[i] && !map[ny][nx].dir[ops])		// No wall each side way.
			{
				que.push(make_pair(ny, nx));
				visit[ny][nx] = true;
				cnt += 1;
			}
		}
	}
	return cnt;
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);	cout.tie(0);
	memset(map, false, sizeof(map));

	cin >> M >> N;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			int val;
			cin >> val;				// Input data.
			Binary(i, j, val);		// Change to useful data.
		}
	}

	int idx = 1, big = 0;			// idx = The number of rooms.
	memset(visit, 0, sizeof(visit));
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			if (!visit[i][j])
			{
				area[idx] = BFS(i, j);
				big = max(big, area[idx]);		// The biggest size of area.
				idx += 1;
			}
		}
	}

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			for (int k = 0; k < 4; k++)
			{
				int ny = i + dy[k];
				int nx = j + dx[k];

				if (ny < 0 || ny >= N || nx < 0 || nx >= M)		// Oveflow.
					continue;

				int op = (k + 2) % 4;
				if (map[i][j].dir[k] && map[ny][nx].dir[op])	 // Delete the wall each side.
				{
					memset(visit, false, sizeof(visit));
					map[i][j].dir[k] = false;
					map[ny][nx].dir[op] = false;
					answer = max(answer, BFS(i, j));		// Exhaustive search from (0,0) to (N,M).
					map[i][j].dir[k] = true;
					map[ny][nx].dir[op] = true;
				}
			}
		}
	}

	cout << idx - 1 << endl;		// The number of rooms.
	cout << big << endl;			// The biggest size of room.
	cout << answer << endl;		// The biggest combined room size.
}