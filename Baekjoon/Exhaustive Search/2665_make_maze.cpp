#include<iostream>
#include<memory.h>
#include<queue>

#define MAX 51

using namespace std;

const int dy[4] = { -1,1,0,0 };
const int dx[4] = { 0,0,-1,1 };

struct location		// The data of location.
{
	int y, x;		// Coordinate.
	int cnt;		// The movement.
};

int N;										// N = The size of map.
char map[MAX][MAX];			// map = The memory of input data.
bool visit[100][MAX][MAX];	// visit = The memory of visited or not.
int answer = 0;						// answer = The shortest way to arrive as output. 

bool BFS(int k)		// To figure out it is possible to arrive at destination with k'th pass.
{	// Initialization.
	memset(visit, false, sizeof(visit));
	visit[0][1][1] = true;

	queue<location> que;
	que.push({ 1,1,0 });		// Basic state.
	while (!que.empty())
	{
		auto cur = que.front();
		que.pop();

		if (cur.y == N && cur.x == N)		// Base case. [Arrive at destination.]
			return true;

		for (int i = 0; i < 4; i++)
		{
			int ny = cur.y + dy[i];
			int nx = cur.x + dx[i];

			if (ny<1 || ny>N || nx<1 || nx>N)		// Overflow.
				continue;

			if (map[ny][nx] == '1' && !visit[cur.cnt][ny][nx])		// Possible to move. + Not visit yet.
			{
				que.push({ ny,nx,cur.cnt });
				visit[cur.cnt][ny][nx] = true;
			}

			else if (map[ny][nx] == '0' && cur.cnt < k)		// Impossible to move. + Possible to pass over.
			{
				if (!visit[cur.cnt + 1][ny][nx])		// Not visit yet.
				{
					que.push({ ny,nx, cur.cnt + 1 });
					visit[cur.cnt + 1][ny][nx] = true;
				}
			}
		}
	}
	return false;
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);	cout.tie(0);

	cin >> N;
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
			cin >> map[i][j];			// Input data.
	}

	int dist = abs(1 - N) + abs(1 - N);		// The distance from departure to destination.
	for (int i = 0; i <= dist; i++)		// From zero To all of cases.
	{
		if (BFS(i))		// To figure out it is possible to arrive or not.
		{
			answer = i;		// The shortest way.
			break;
		}
	}
	cout << answer << endl;		// Output.
}