#include<iostream>
#include<algorithm>
#include<memory.h>
#include<vector>
#pragma warning(disable:4996)

#define MAX 101
#define INF 987654321

using namespace std;

const int dy[4] = { -1,1,0,0 };		// Up, Down.
const int dx[4] = { 0,0,-1,1 };		// Left, Right.

int N;			// N = The size of map.
int map[MAX][MAX];			// map = The memory of original input data.
int cache[MAX][MAX];
bool visit[MAX][MAX];			// visit = The memory of visited or not.
int answer = INF;		// answer = The minimum time to arrive destination as output.

void DFS(int y, int x, int cnt)
{
	if (cnt >= answer)	// Base case.
		return;
	
	if (y == N - 1 && x == N - 1)	// Base case.
	{
		answer = min(answer, cnt);
		return;
	}
	
	cache[y][x] = min(cache[y][x], cnt);

	for (int i = 0; i < 4; i++)
	{
		int ny = y + dy[i];
		int nx = x + dx[i];

		if (ny < 0 || ny >= N || nx < 0 || nx >= N)		// Overflow.
			continue;

		if (!visit[ny][nx] && cnt + map[ny][nx] <= cache[ny][nx])
		{
			visit[ny][nx] = true;
			DFS(ny, nx, cnt + map[ny][nx]);
			visit[ny][nx] = false;
		}
	}
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	freopen("input.txt", "r", stdin);

	int test_case;
	cin >> test_case;
	for (int t = 1; t <= test_case; t++)
	{	// Initialization.
		memset(map, 0, sizeof(map));
		memset(visit, false, sizeof(visit));
		answer = INF;

		cin >> N;
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				char ch;
				cin >> ch;
				map[i][j] = ch - '0';
			}
		}

		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
				cache[i][j] = INF;
		}
		DFS(0, 0, 0);

		cout << "#" << t << " " << answer << endl;
	}
}
