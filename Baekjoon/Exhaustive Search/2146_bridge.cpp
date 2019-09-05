#include<iostream>
#include<algorithm>
#include<memory.h>
#include<queue>

#define MAX 101
#define INF 987654321

using namespace std;

const int dy[4] = { -1,1,0,0 };
const int dx[4] = { 0,0,-1,1 };

struct Way		// The bridge's data.
{	
	int y, x;		// Location.
	int dist;		// Distance.
};

int N, K = 0;					// N = The size of map.			K = The value of each island.
int map[MAX][MAX];		// map = The memory of original input data.
bool visit[MAX][MAX];		// visit = The memory of visited or not.
int answer = INF;				// answer = The shortest way to connect islands as output.

bool Range(int y, int x)		// To check whether it is overflow or not.
{
	if (y < 0 || y >= N || x < 0 || x >= N)	// Overflow.
		return false;
	return true;
}

void BFS(int num)		// To figure out the distance of bridge to connect each island.
{
	memset(visit, false, sizeof(visit));		// Initialization.
	queue<Way> que;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (map[i][j] == num)			// The whole of island coordinate.
			{
				que.push({ i,j,0 });
				visit[i][j] = true;
			}
		}
	}

	int result = INF;
	while (!que.empty())
	{
		auto cur = que.front();
		que.pop();

		for (int i = 0; i < 4; i++)		// Four directions.
		{
			int ny = cur.y + dy[i];
			int nx = cur.x + dx[i];

			if (!Range(ny, nx))			// Overflow.
				continue;

			if (map[ny][nx] > 0 && map[ny][nx] != num)	// Continent + Other island.
				result = min(result, cur.dist);		// Compare the shortest distance.

			else if (!visit[ny][nx] && map[ny][nx] == 0)		// Not visited yet + Ocean. 
			{
				visit[ny][nx] = true;
				que.push({ ny,nx,cur.dist + 1 });
			}
		}
	}
	answer = min(answer, result);		// Compare the shortest way.
}

void DFS(int y, int x, int num)		// To figure out where the island is and distinguish from others.
{
	visit[y][x] = true;
	map[y][x] = num;		// Labeling.

	for (int i = 0; i < 4; i++)	// Four directions.
	{
		int ny = y + dy[i];
		int nx = x + dx[i];

		if (!Range(ny, nx))		// Overflow.
			continue;

		if (!visit[ny][nx] && map[ny][nx] != 0)		// Not visited yet + Continent.
			DFS(ny, nx, num);
	}
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> N;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
			cin >> map[i][j];			// Original input.
	}

	memset(visit, false, sizeof(visit));
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (map[i][j] == 1 && !visit[i][j])		// Figure out the island.
				DFS(i, j, ++K);
		}
	}

	for (int i = 1; i <= K; i++)		// Figure out the bridge.
		BFS(i);
	
	cout << answer << endl;		// Output.
}