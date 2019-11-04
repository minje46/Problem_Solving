#include<iostream>
#include<memory.h>
#include<queue>
//#pragma warning(disable:4996)

#define MAX 301

using namespace std;

const int dy[8] = { -1, -1, -1,0,0,1,1,1 };
const int dx[8] = { -1,0,1,-1,1,-1,0,1 };

int N;								// N = The size of map.
char map[MAX][MAX];	// map = The memory of input data.	
int cnt[MAX][MAX];		// cnt = The memory of number of mines.
bool visit[MAX][MAX];		// visit = The memory of visited or not.
vector<pair<int, int>> vc;	// vc = The memory of safe state's location.
int answer;						// answer = The minimum number of clicked to find all of mines as output.

bool Range(int ny, int nx)		// To figure out the correct range or not.
{
	if (ny < 0 || ny >= N || nx < 0 || nx >= N)		// Overflow.
		return false;
	return true;
}

int Count(int y, int x)		// To count the number of mines around map[y][x].
{
	int cnt = 0;
	for (int k = 0; k < 8; k++)
	{
		int ny = y + dy[k];
		int nx = x + dx[k];

		if (!Range(ny, nx))			// Overflow.
			continue;

		if (map[ny][nx] == '*')	// Mine.
			cnt += 1;					// Count.
	}
	return cnt;
}

void BFS(int y, int x)		// To do exhaustive search when the map[y][x] is '0'.
{
	queue<pair<int, int>> que;
	que.push(make_pair(y, x));
	visit[y][x] = true;
	map[y][x] = cnt[y][x] + '0';
	while (!que.empty())
	{
		auto cur = que.front();
		que.pop();

		if (cnt[cur.first][cur.second] == 0)	// The case of clean zone.
		{
			for (int i = 0; i < 8; i++)				// Chaining.
			{
				int ny = cur.first + dy[i];
				int nx = cur.second + dx[i];

				if (!Range(ny, nx) || visit[ny][nx])	// Overflow.
					continue;

				visit[ny][nx] = true;
				map[ny][nx] = cnt[ny][nx] + '0';
				que.push(make_pair(ny, nx));
			}
		}
	}
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);	cout.tie(0);

//	freopen("input.txt", "r", stdin);
	int test_case;
	cin >> test_case;
	for (int t = 1; t <= test_case; t++)
	{	// Initialization.
		memset(cnt, 0, sizeof(cnt));
		memset(visit, false, sizeof(visit));
		vc.clear();
		answer = 0;

		cin >> N;
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
				cin >> map[i][j];		// Input data.
		}

		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				if (map[i][j] == '.')		// In the whole of empty space.
				{
					cnt[i][j] = Count(i, j);
					if (cnt[i][j] == 0)		// Clean zone. [Adjacent에 지뢰가 없는 경우를 무조건 먼저 처리해주어야 한다. → 최소값을 위해.]
						vc.push_back(make_pair(i, j));		// Clean zone is the only way to get the minium number of clicked.
				}
			}
		}

		for (int i = 0; i < vc.size(); i++)	// For chaining clicked.
		{
			if (visit[vc[i].first][vc[i].second])		// Already visited.
				continue;
			answer += 1;		
			BFS(vc[i].first, vc[i].second);		// Spread out.
		}

		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				if (map[i][j] == '.')
					answer += 1;			// Count the independent one. [Impossible to chain.]
			}
		}
		cout << "#" << t << " " << answer << endl;		// Output.
	}
}