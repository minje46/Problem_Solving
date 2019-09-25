#include<iostream>
#include<algorithm>
#include<memory.h>
#include<vector>
#include<queue>

#define MAX 11
#define ISLAND 7
#define INF 987654321

using namespace std;

const int dy[4] = { -1,1,0,0 };
const int dx[4] = { 0,0,-1,1 };

struct Bridge
{
	pair<int, int> dpt, dst;
	int len;
	bool used;
};

int N, M;							// N = The height of map.			M = The width of map.
int map[MAX][MAX];		// map = The memory of original map.
bool visit[MAX][MAX];		// visit = The memory of whether it is visited or not.
vector<Bridge> bridge;
bool check[ISLAND];
int num = 1, answer = INF;

bool Range(int y, int x)		// To figure out this location is possible or not.
{
	if (y < 0 || y >= N || x < 0 || x >= M)	// Overflow.
		return false;
	return true;
}

bool Find(pair<int, int> start, pair<int, int> end)
{
	for (int i = 0; i < bridge.size(); i++)
	{
		if (bridge[i].dpt == end && bridge[i].dst == start)
			return false;
	}
	return true;
}

int Count()
{
	int tot = 0;
	for (int i = 0; i < bridge.size(); i++)
	{
		if (!bridge[i].used)
			tot += bridge[i].len;
	}
	return tot;
}

void Arrive(int cur)
{
	if (check[cur])
		return;

	check[cur] = true;

	for (int i = 0; i < bridge.size(); i++)
	{
		if (!bridge[i].used)
		{
			int start = map[bridge[i].dpt.first][bridge[i].dpt.second];
			int end = map[bridge[i].dst.first][bridge[i].dst.second];

			if (cur == start)
				Arrive(end);
			if (cur == end)
				Arrive(start);
		}
	}
}

bool Possible()
{
	for (int k = 1; k < num; k++)
	{
		memset(check, false, sizeof(check));
		Arrive(k);
		for (int i = 1; i < num; i++)
		{
			if (!check[i])
				return false;
		}
	}
	return true;
}

void BFS(int y, int x, int num)		// To make the isalnd group based on bfs.
{
	queue<pair<int, int>>que;
	que.push(make_pair(y, x));		// From the departure position.

	while (!que.empty())
	{
		auto cur = que.front();
		que.pop();

		visit[cur.first][cur.second] = true;			
		map[cur.first][cur.second] = num;		// Make same group.

		for (int i = 0; i < 4; i++)
		{
			int ny = cur.first + dy[i];
			int nx = cur.second + dx[i];

			if (!Range(ny, nx))		// Overflow.
				continue;

			if (!visit[ny][nx] && map[ny][nx] != 0)		// Not visited yet. + Continent.
				que.push(make_pair(ny, nx));
		}
	}
}

void Connected(int y, int x)
{
	for (int dir = 0; dir < 4; dir++)
	{
		int ny = y + dy[dir];
		int nx = x + dx[dir];
		int len = 0;

		//while (Range(ny, nx) && map[ny][nx] == 0)	// Not overflow + Not continent.
		while (true)
		{
			if (!Range(ny, nx))
				break;

			if (map[ny][nx] > 0)
			{
				if (len >= 2 && Find({ y,x }, { ny,nx }))
					bridge.push_back({ {y,x}, {ny,nx}, len, false });
				break;
			}
			ny += dy[dir];
			nx += dx[dir];
			len += 1;
		}		
	}
}

void DFS(int idx, int cnt, int target)
{
	if (cnt == target)
	{
		if (Possible())
			answer = min(answer, Count());
		return;
	}

	if (idx >= bridge.size())
		return;

	bridge[idx].used = true;
	DFS(idx + 1, cnt + 1, target);
	bridge[idx].used = false;
	DFS(idx + 1, cnt, target);
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> N >> M;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
			cin >> map[i][j];			// Input of map.
	}

	memset(visit, false, sizeof(visit));		// Initialization.
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			if (map[i][j] != 0 && !visit[i][j])		// Continent + Not visited yet.
				BFS(i, j, num++);						// Make a island group.
		}
	}

	memset(visit, false, sizeof(visit));
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			if (map[i][j] > 0 && !visit[i][j])
			{
				visit[i][j] = true;
				Connected(i, j);
			}
		}
	}

	int n = bridge.size();
	for (int i = 0; i < n; i++)
		DFS(0, 0, i);

	if (answer == INF)
		answer = -1;
	cout << answer << endl;
}