#include<iostream>
#include<algorithm>
#include<memory.h>
#include<queue>

#define MAX 105
#define INF 987654321

using namespace std;

const int dy[4] = { -1,1,0,0 };
const int dx[4] = { 0,0,-1,1 };

struct location		// Location data.
{
	int y, x;			// Location.	
	int cnt;			// Count.	
};

struct compare	// Customized compare.
{
	bool operator()(const location &a, const location &b)
	{
		if (a.cnt == b.cnt)
		{
			if (a.y == b.y)
				return a.x > b.x;
			return a.y > b.y;
		}
		return a.cnt > b.cnt;
	}
};

int H, W;							// H = The height of map.				W = The width of map.
char map[MAX][MAX];		// map = The memory of input data.
int visit[3][MAX][MAX];		// visit = The memory of visited or not.
pair<int, int>prisoner[2];		// prisoner = The location of prisoners.
int answer = 0;					// answer = The shortest way to escape as output.

void BFS(int idx, int y, int x)		// To figure out the way they moved.
{
	priority_queue<location, vector<location>, compare> que;		// To pick the shortest distance first.
	que.push({ y,x,0 });
	visit[idx][y][x] = 0;
	while (!que.empty())
	{
		auto cur = que.top();
		que.pop();

		for (int i = 0; i < 4; i++)
		{
			int ny = cur.y + dy[i];
			int nx = cur.x + dx[i];

			if (ny < 0 || ny > H+1 || nx < 0 || nx > W+1)		// Overflow.
				continue;
			
			if (visit[idx][ny][nx] == -1 && map[ny][nx] != '*')		// Not visit yet.	+ Not wall.
			{
				if (map[ny][nx] == '#')		// Door.
				{
					que.push({ ny,nx, cur.cnt + 1 });		// Take the count.
					visit[idx][ny][nx] = cur.cnt + 1;
				}
				else
				{
					que.push({ ny,nx, cur.cnt });		// Empty space.
					visit[idx][ny][nx] = cur.cnt;			// Move freely.
				}
			}
		}
	}
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);	cout.tie(0);

	int test_case;
	cin >> test_case;
	for (int t = 1; t <= test_case; t++)
	{	// Initialization.
		memset(visit, -1, sizeof(visit));
		answer = INF;
		int idx = 0;

		cin >> H >> W;
		for (int i = 1; i <= H; i++)
		{
			for (int j = 1; j <= W; j++)
			{
				cin >> map[i][j];				// Input data.
				if (map[i][j] == '$')				// Prisoner location.
					prisoner[idx++] = { i,j };
			}
		}
		for (int i = 0; i <= H + 1; i++)			// Extend the map.
		{
			map[i][0] = '.';
			map[i][W + 1] = '.';
		}
		for (int j = 0; j <= W + 1; j++)		// For searching out side to inside.
		{
			map[0][j] = '.';
			map[H + 1][j] = '.';
		}

		BFS(0, 0, 0);		// Move from outside to inside.
		BFS(1, prisoner[0].first, prisoner[0].second);		// Move the first prisoner to outside.
		BFS(2, prisoner[1].first, prisoner[1].second);		// Move the second prisoner to outside.	

		for (int i = 1; i <= H; i++)
		{
			for (int j = 1; j <= W; j++)
			{
				if (map[i][j] != '*')		// Not wall.
				{
					int dist = 0;
					for (int k = 0; k < 3; k++)		// The distance to arrive at.
						dist += visit[k][i][j];
					if (map[i][j] == '#')				// If there is door,
						dist -= 2;						// It doesn't need to take care more than one.

					if (dist >= 0)						// The minimum way to escape.
						answer = min(answer, dist);
				}
			}
		}

		cout << answer << endl;			// Output.
	}
}