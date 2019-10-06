#include<iostream>
#include<algorithm>
#include<memory.h>
#include<queue>
#include<vector>

#define MAX 51

using namespace std;

const int dy[4] = { -1,1,0,0 };
const int dx[4] = { 0,0,-1,1 };

int N, M, K;					// N = The height of mpa.				M = The width of map.				K = The number of cabbages.
int map[MAX][MAX];		// map = The memory of input data.
bool visit[MAX][MAX];		// visit = The memory of visited or not.

void BFS(int y, int x, int idx)		// To make a group as bfs algorithm.	
{
	queue<pair<int, int>> que;
	que.push(make_pair(y, x));
	visit[y][x] = true;
	map[y][x] = idx;		// Group number.
	while (!que.empty())
	{
		auto cur = que.front();
		que.pop();

		for (int i = 0; i < 4; i++)
		{
			int ny = cur.first + dy[i];
			int nx = cur.second + dx[i];

			if (ny < 0 || ny >= N || nx < 0 || nx >= M)		// Overflow.
				continue;

			if (!visit[ny][nx] && map[ny][nx] == 1)		// Not visited yet. + Cabbage.
			{
				visit[ny][nx] = true;		// visited.
				map[ny][nx] = idx;		// Numbering.
				que.push(make_pair(ny, nx));
			}
		}
	}
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int test_case;
	cin >> test_case;
	for (int t = 1; t <= test_case; t++)
	{	// Initialization.
		memset(map, 0, sizeof(map));
		memset(visit, false, sizeof(visit));

		cin >> M >> N >> K;			// Input of map size and cabbages.
		for (int i = 0; i < K; i++)
		{
			int y, x;
			cin >> x >> y;
			map[y][x] = 1;				// Input map data.
		}

		int idx = 0;
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < M; j++)
			{
				if (!visit[i][j] && map[i][j] == 1)		// Not visited yet. + Cabbage.
					BFS(i, j, ++idx);			// BFS algorithm.
			}
		}
		cout << idx  << endl;		// Output.
	}
}