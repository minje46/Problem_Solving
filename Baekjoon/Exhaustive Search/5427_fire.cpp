#include<iostream>
#include<memory.h>
#include<queue>

#define MAX 1001
#define INF 987654321

using namespace std;

const int dy[4] = { -1,1,0,0 };
const int dx[4] = { 0,0,-1,1 };

struct location		// The person's location.
{
	int y, x;			// Location.
	int cnt;			// Move from departure.
};

struct compare	// Compare method for priority queue.
{
	bool operator()(const location &a, const location &b)
	{
		if (a.cnt == b.cnt)
		{
			if (a.y == a.x)
				return a.x < b.y;		// Ascending.	
			return a.y < b.y;			// Ascending.
		}
		return a.cnt > b.cnt;		// Descending sort.
	}
};

int W, H;						// W = The width of map.				H = The height of map.
char map[MAX][MAX];	// map = The memory of input data.
bool visit[MAX][MAX];		// visit = The memory of visited or not.
queue<pair<int, int>>fire;	// fire = The memory of fire's location.
pair<int, int> dpt;			// dpt = The departure location.
int answer = INF;				// answer = The shortest way to escape as output.

bool Range(int y, int x)		// To figure out it is overflow or not.
{
	if (y < 0 || y >= H || x < 0 || x >= W)	// Overflow.
		return false;
	return true;
}

void Expand()		// To expand the fire's location.
{
	int n = fire.size();		// The original size before addition.
	for (int i = 0; i < n; i++)
	{
		int y = fire.front().first;
		int x = fire.front().second;
		fire.pop();			// The previous one doesn't need to take care.
		for (int i = 0; i < 4; i++)
		{
			int ny = y + dy[i];
			int nx = x + dx[i];

			if (!Range(ny, nx))		// Overflow.
				continue;

			if (map[ny][nx] == '.')		// Only empty space.
			{
				map[ny][nx] = '*';		// Treat as fire.
				fire.push(make_pair(ny, nx));
			}
		}
	}
}

void BFS()		// To figure out the shortest way to escape based on bfs.
{
	priority_queue<location, vector<location>, compare> que;		// To check the change of time.
	que.push({ dpt.first, dpt.second, 1 });									// It is the criteria for expansion.	
	int time = 0;
	while (!que.empty())
	{
		auto cur = que.top();
		que.pop();

		if (cur.cnt > time)		// The fire expansion was dealt first.
		{
			Expand();				// Expand the fire.
			time += 1;				// Check the time.
		}
		for (int i = 0; i < 4; i++)
		{
			int ny = cur.y + dy[i];
			int nx = cur.x + dx[i];

			if (!Range(ny, nx))	// Overflow. + Escape.
			{
				answer = cur.cnt;	// The time to escape.
				return;
			}

			if (!visit[ny][nx] && map[ny][nx] == '.')		// Not visited yet. + Empty space to move.
			{
				visit[ny][nx] = true;
				que.push({ ny,nx, cur.cnt + 1 });
			}
		}
	}
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int test_case;
	cin >> test_case;
	for (int t = 1; t <= test_case; t++)
	{	// Initialization.
		memset(map, ' ', sizeof(map));
		memset(visit, false, sizeof(visit));
		while (!fire.empty())
			fire.pop();
		answer = INF;

		cin >> W >> H;
		for (int i = 0; i < H; i++)
		{
			for (int j = 0; j <W; j++)
			{
				cin >> map[i][j];			// Input of map data.
				if (map[i][j] == '@')		// Departure.
					dpt = { i,j };
				else if (map[i][j] == '*')	// Fire.
					fire.push(make_pair(i, j));
			}
		}

		visit[dpt.first][dpt.second] = true;
		map[dpt.first][dpt.second] = '.';
		BFS();		// bfs algorithm.

		if (answer == INF)		// Impossible case.
			cout << "IMPOSSIBLE" << endl;
		else							// Shortest way to escape.
			cout << answer << endl;
	}
}