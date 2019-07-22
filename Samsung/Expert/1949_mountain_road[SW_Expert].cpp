#include<iostream>
#include<algorithm>
#include<vector>
#include<memory.h>
//#pragma warning(disable:4996)

#define MAX 9

using namespace std;

int N, K, answer = -1;			// N = The size of map.		K = The height to construct.		answer = The output.
int map[MAX][MAX];			// map = The memory of map.
bool visit[MAX][MAX];			// visit = The memory of visited or not.
int dy[4] = { -1,1,0,0 };		// Up, Down.
int dx[4] = { 0,0,-1,1 };		// Left, Right.
vector<pair<int, int>> peak;	// peak = The memory of peak's location. 

void DFS(int y, int x, int len, bool flag)		// To figure out the possible mountain road to organize.
{
	answer = max(answer, len);		// To set the max length of mountain road.
	visit[y][x] = true;			// Check it was visited now for avoiding overlap.

	for (int i = 0; i < 4; i++)	// Up, Down, Left, Right.
	{
		int ny = y + dy[i];
		int nx = x + dx[i];

		if (ny <1 || ny>N || nx<1 || nx>N || visit[ny][nx])		// Overflow and visit again.
			continue;

		if (map[y][x] > map[ny][nx])		// The condition of mountain road.
		{
			DFS(ny, nx, len + 1, flag);
			visit[ny][nx] = false;				// Reset this site as not visited for other searching.
		}

		else
		{
			if (!flag &&map[y][x] > map[ny][nx] - K)		// Not construction yet. && Possible condition of construction.
			{
				int tmp = map[ny][nx];		// Remember the original value.

				while (map[y][x] <= map[ny][nx])		// To do construct mountain as smaller as they can.
					map[ny][nx]--;				// Modify the original value here.

				DFS(ny, nx, len + 1, !flag);	// The construction was made, flag value should be changed as well.
				visit[ny][nx] = false;
				map[ny][nx] = tmp;			// Reset the map as original value.
			}
		}
	}
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);

//	freopen("input.txt", "r", stdin);

	int T;				// T = The number of test cases.
	cin >> T;
	for (int t = 1; t <= T; t++)
	{	// Initialize.
		answer = -1;
		memset(map, -1, sizeof(map));
		peak.clear();
		cin >> N >> K;

		int max_h = -1;					// For getting the highest height.	
		for (int i = 1; i <= N; i++)		// Input the map.
		{
			for (int j = 1; j <= N; j++)
			{
				cin >> map[i][j];
				max_h = max(max_h, map[i][j]);
			}
		}

		for (int i = 1; i <= N; i++)			// Find the peak location.
		{
			for (int j = 1; j <= N; j++)
				if (max_h == map[i][j])	// Based on highest height.	
					peak.push_back(make_pair(i, j));
		}

		for (int i = 0; i < peak.size(); i++)		// To exhaustive search in all peaks.
		{
			bool flag = false;
			memset(visit, false, sizeof(visit));	
			DFS(peak[i].first, peak[i].second, 1, flag);
		}

		cout << "#" << t << " " << answer << endl;		// The longest mountain road.
	}
}