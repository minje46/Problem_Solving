#include<iostream>
#include<algorithm>
#include<memory.h>
#include<queue>
#include<string>
#include<vector>

#define MAX 26

using namespace std;

const int dy[4] = { -1,1,0,0 };
const int dx[4] = { 0,0,-1,1 };

int N;									// N = The size of map.
int map[MAX][MAX];			// map = The memory of input data.
bool visit[MAX][MAX];			// visit = The memory of visited or not.
queue<pair<int, int>> que;	// que = The memory for bfs.

int BFS(int y, int x, int idx)	// To make a group as bfs algorithm.	
{
	int cnt = 1;		// The number of members in group.
	que.push(make_pair(y, x));
	visit[y][x] = true;
	map[y][x] = idx;			// Group number.
	while (!que.empty())
	{
		auto cur = que.front();
		que.pop();

		for (int i = 0; i < 4; i++)
		{
			int ny = cur.first + dy[i];
			int nx = cur.second + dx[i];

			if (ny < 0 || ny >= N || nx < 0 || nx >= N)		// Overflow.
				continue;

			if (!visit[ny][nx] && map[ny][nx] == 1)			// Not visit yet. + Possible to make a group.
			{
				visit[ny][nx] = true;			// Visited.	
				que.push(make_pair(ny, nx));
				map[ny][nx] = idx;			// Numbering.
				cnt += 1;						// Counting.
			}
		}
	}
	return cnt;			// The number of memebers in group.
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	memset(map, 0, sizeof(map));
	cin >> N;				// The size of map.
	for (int i = 0; i < N; i++)
	{
		string str;
		cin >> str;			// String type.
		for (int j = 0; j < str.length(); j++)
			map[i][j] = str[j] - '0';		// Map data.
	}

	memset(visit, false, sizeof(visit));		// Initialization.
	vector<int> vc;		// The numebr of members in each group.
	int idx = 1;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (!visit[i][j] && map[i][j] == 1)		// Not visit yet. + Possible to make a group.
			{
				int group = BFS(i, j, idx);		// Build a group.
				vc.push_back(group);		
				idx += 1;
			}
		}
	}

	sort(vc.begin(), vc.end());		// Ascending sort.
	cout << vc.size() << endl;		// The total number of groups.
	for (int i = 0; i < vc.size(); i++)
		cout << vc[i] << endl;			// The numeber of members in each group.
}