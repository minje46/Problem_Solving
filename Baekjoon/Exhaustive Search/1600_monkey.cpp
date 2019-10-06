#include<iostream>
#include<algorithm>
#include<memory.h>
#include<queue>

#define MAX 201
#define INF 987654321

using namespace std;

const int dy[4] = { -1,1,0,0 };
const int dx[4] = { 0,0,-1,1 };
const int night[8][2] = { { -2,-1 },{ -2,1 },{ -1,-2 },{ -1,2 },{ 1,-2 },{ 1,2 },{ 2,-1 },{ 2,1 } };

struct location		// The data for movement.
{
	int y, x;			// Location.
	int horse;		// Night's movement.
	int cnt;			// Movement time.
};

int K, W, H;						// K = The number of movement as horse.			W = The width of map.			H = The height of map.
int map[MAX][MAX];			// map = The memory of input data.
bool visit[MAX][MAX][32];	// visit = The memory of visited or not.
int answer = INF;					// answer = The minimum movement arrive at destination as output.

void BFS()		// To figure out the monkey's movement to arrive at destination with knight movement as well.
{
	queue<location>que;
	que.push({ 0, 0, 0, 0 });
	while (!que.empty())
	{
		auto cur = que.front();		// Current one.
		que.pop();

		if (cur.cnt > answer)		// Not need to take care.
			continue;

		if (cur.y == (H - 1) && cur.x == (W - 1))		// Arrive at destination.
			answer = min(answer, cur.cnt);

		if (cur.horse < K)				// If the knight's movement is possible.
		{
			for (int i = 0; i < 8; i++)
			{
				int ny = cur.y + night[i][0];
				int nx = cur.x + night[i][1];

				if (ny < 0 || ny >= H || nx < 0 || nx >= W)		// Overflow.
					continue;

				if (!visit[ny][nx][cur.horse + 1] && map[ny][nx] == 0)	// Use knight's movement.
				{
					visit[ny][nx][cur.horse + 1] = true;
					que.push({ ny,nx,cur.horse + 1, cur.cnt + 1 });
				}
			}
		}

		for (int i = 0; i < 4; i++)
		{
			int ny = cur.y + dy[i];
			int nx = cur.x + dx[i];

			if (ny < 0 || ny >= H || nx < 0 || nx >= W)		// Overflow.
				continue;

			if (!visit[ny][nx][cur.horse] && map[ny][nx] == 0)		// Base movement.
			{
				visit[ny][nx][cur.horse] = true;
				que.push({ ny,nx,cur.horse, cur.cnt + 1 });
			}
		}
	}
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	// Initialization.
	memset(map, 0, sizeof(map));
	memset(visit, false, sizeof(visit));
	cin >> K >> W >> H;
	for (int i = 0; i < H; i++)
	{
		for (int j = 0; j < W; j++)
			cin >> map[i][j];		// Input.
	}
	
	visit[0][0][0] = true;
	BFS();		// BFS.

	if (answer == INF)		// Impossible case.
		answer = -1;
	cout << answer << endl;		// Output.
}