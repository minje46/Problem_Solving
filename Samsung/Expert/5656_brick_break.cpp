#include<iostream>
#include<algorithm>
#include<memory.h>
#include<vector>
#include<queue>
#include<stack>
//#pragma warning(disable:4996)

#define MAX_N 5
#define MAX_H 16
#define MAX_W 13
#define INF 987654321

using namespace std;

const int dy[4] = { -1,1,0,0 };		// Up, Down.
const int dx[4] = { 0,0,-1,1 };		// Left, Right.

struct Brick		// The data of brick.
{
	int y, x;		// Location.
	int range;	// Range.
};

int N, W, H;			// N = The number of shoot.			W = The width of map.				H = The height of map.
int map[MAX_N][MAX_H][MAX_W];			// map = The memory of map data. [0 : original. 1~4 : Result map after brick break.]
int answer = INF;		// answer = The number of bricks as output.

void Copied(int dpt, int dst)		// To copy the original map data to target map data.
{
	for (int i = 0; i < H; i++)		// map[0] : Original input map.
	{										// map[1~4] : Updated map brick breaked.
		for (int j = 0; j < W; j++)
			map[dst][i][j] = map[dpt][i][j];
	}
}

int Count()		// To count the remaining bricks after brick break.
{
	int cnt = 0;
	for (int i = 0; i < H; i++)
	{
		for (int j = 0; j < W; j++)
		{
			if (map[N][i][j] > 0)		// N is the target number to shoot.
				cnt++;						// After N'th shooting, how many bricks remain.
		}
	}
	return cnt;
}

vector<pair<int, int>> Peak(int idx)		// To figure out the peak location on the map.
{														// [Map에서 peak인 것만 shooting 가능하기 때문에 이용.]	
	vector<pair<int, int>> h;
	bool visit[MAX_W];							// To decrease the time consumed.
	memset(visit, false, sizeof(visit));

	for (int i = 0; i < H; i++)
	{
		for (int j = 0; j < W; j++)
		{
			if (!visit[j] && map[idx][i][j] > 0)		// It takes care only the highest one in each column.
			{
				h.push_back(make_pair(i, j));
				visit[j] = true;
			}
		}
	}
	return h;
}

void Update(int idx)			// To update the current map after brick break.
{
	for (int j = 0; j < W; j++)
	{
		stack<int>stk;			// Use the FILO.
		for (int i = 0; i < H; i++)
		{
			if (map[idx][i][j] > 0)
			{
				stk.push(map[idx][i][j]);		// Push the only brick.
				map[idx][i][j] = 0;
			}
		}
		int k = H - 1;			// Then update the brick from beneath.
		while (!stk.empty())
		{
			map[idx][k--][j] = stk.top();
			stk.pop();
		}
	}
}

void Shoot(int y, int x, int idx, int r)		// To break bricks from current location to r'th range.
{
	queue<Brick> que;
	que.push({ y,x,r });
	while (!que.empty())
	{
		auto cur = que.front();
		que.pop();

		map[idx + 1][cur.y][cur.x] = 0;	// Brick breaks.

		for (int i = 0; i < 4; i++)		// Up,Down,Left,Right.
		{
			for (int r = 1; r < cur.range; r++)	// In range.
			{
				int ny = cur.y + dy[i] * r;
				int nx = cur.x + dx[i] * r;

				if (ny < 0 || ny >= H || nx < 0 || nx >= W)		// Overflow.
					continue;

				if (map[idx + 1][ny][nx] >= 1)		// Takes care only brick.
					que.push({ ny, nx, map[idx + 1][ny][nx] });
			}
		}
	}
	Update(idx + 1);		// Should update after broke.
}

void DFS(int idx, vector<pair<int, int>> h)		// To do exhaustive search in the whole of cases.
{
	if (idx == N)		// Base case. [N'th shooting.]
	{
		answer = min(answer, Count());		// Compare the minimum remaining.
		return;
	}

	for (int i = 0; i < h.size(); i++)
	{
		Copied(idx, idx + 1);		// Return to previous map data.
		Shoot(h[i].first, h[i].second, idx, map[idx][h[i].first][h[i].second]);		// Break bricks with i'th peak.
		DFS(idx + 1, Peak(idx + 1));		// Recursively.
	}
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	//	freopen("input.txt", "r", stdin);

	int test_case;
	cin >> test_case;
	for (int t = 1; t <= test_case; t++)
	{	// Initialization.
		memset(map, 0, sizeof(map));
		answer = INF;

		cin >> N >> W >> H;
		for (int i = 0; i < H; i++)
		{
			for (int j = 0; j < W; j++)
				cin >> map[0][i][j];		// Original input data.
		}


		vector<pair<int, int>> height = Peak(0);		// The base case of highest location.
		DFS(0, height);		// Simulation.

		if (answer == INF)	// The case of all cleared.
			answer = 0;

		cout << "#" << t << " " << answer << endl;		// Output.
	}
}