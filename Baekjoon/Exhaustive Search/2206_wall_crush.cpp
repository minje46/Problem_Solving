#include<iostream>
#include<queue>

#define MAX 1001

using namespace std;

const int dy[4] = { -1,1,0,0 };
const int dx[4] = { 0,0,-1,1 };

struct location
{
	int y, x;
	bool crush;
};

int N, M;							// N = The height of mpa.				M = The width of map.
char map[MAX][MAX];	// map = The memory of input data.
int visit[2][MAX][MAX];	// visit = The memory of visited or not.

int BFS(void)		// To figure out the shortest way to arrive at destination.
{
	queue<location> que;
	que.push({ 1,1,true });
	visit[1][1][1] = 1;
	while (!que.empty())
	{
		auto cur = que.front();
		que.pop();

		if (cur.y == N && cur.x == M)		// Base case. [Destination.]
			return visit[cur.crush][cur.y][cur.x];

		for (int i = 0; i < 4; i++)
		{
			int ny = cur.y + dy[i];
			int nx = cur.x + dx[i];

			if (ny<1 || ny>N || nx<1 || nx>M)		// Overflow.
				continue;

			if (visit[cur.crush][ny][nx] == 0 && map[ny][nx] == '0')		// Not visited yet. + Empty space.
			{
				visit[cur.crush][ny][nx] = visit[cur.crush][cur.y][cur.x] + 1;
				que.push({ ny,nx, cur.crush });
			}
			else if (map[ny][nx] == '1' && cur.crush)			// Wall. + Possible to crush.
			{
				visit[!cur.crush][ny][nx] = visit[cur.crush][cur.y][cur.x] + 1;
				que.push({ ny,nx,false });
			}
		}
	}
	return -1;			// Impossible case.
}


int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);	cout.tie(0);

	cin >> N >> M;						// The size of map.
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= M; j++)
			cin >> map[i][j];			// Input data.
	}

	cout << BFS() << endl;			// Output.
}