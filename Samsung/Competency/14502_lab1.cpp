#include<iostream>
#include<algorithm>
#include<memory.h>
#include<vector>
#include<queue>

#define MAX 9
#define WALL 3

using namespace std;

const int dy[4] = { -1,1,0,0 };		// UP, Down.
const int dx[4] = { 0,0,-1,1 };		// Left, Right.

int N, M;				// N = The height of map.		M = The width of map.
int map[MAX][MAX];				// map = The memory of original input data.
vector<pair<int, int>> candi;		// candi = The memory of candidates which is able to build wall.
vector<pair<int, int>> virus;		// virus = The memory of virus location.
bool visit[MAX][MAX];				// visit = The memory of visited or not.
int answer = 0;						// answer = The maximum number of safe area as output.

int Count()		// To count the number of safe area.
{
	int cnt = 0;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{			
			if (!visit[i][j] && map[i][j] == 0)		// Not virus zone + Empty space.
				cnt++;										// [visit = true] means virus alives.
		}
	}
	return cnt;
}

void Virus()			// To spread the whole of viruses using bfs.
{
	memset(visit, false, sizeof(visit));		// Initialization.

	queue<pair<int, int>>que;				// Basic virus's location.
	for (int i = 0; i < virus.size(); i++)	
		que.push(make_pair(virus[i].first, virus[i].second));

	while (!que.empty())
	{
		int y = que.front().first;
		int x = que.front().second;
		que.pop();

		visit[y][x] = true;		// Spreaded.

		for (int i = 0; i < 4; i++)
		{
			int ny = y + dy[i];
			int nx = x + dx[i];

			if (ny < 0 || ny >= N || nx < 0 || nx >= M)		// Overflow.
				continue;

			if (map[ny][nx] == 0 && !visit[ny][nx])			// Empty space + Not spreaded yet.
				que.push(make_pair(ny, nx));
		}
	}
}

void DFS(int idx, int cnt)		// To do exhaustive search with combinations.
{
	if (cnt >= WALL)		// Base case. [Three walls should be installed.
	{
		Virus();			// Spread the whole of viruses after installed wall.
		answer = max(answer, Count());		// Compare the number of safe areas.
		return;
	}

	if (idx >= candi.size())		// Base case. [Overflow.]
		return;

	map[candi[idx].first][candi[idx].second] = 1;		// Treated as installed.
	DFS(idx + 1, cnt + 1);		
	map[candi[idx].first][candi[idx].second] = 0;		// Return to previous.
	DFS(idx + 1, cnt);
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> N >> M;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			cin >> map[i][j];		// Input.

			if (map[i][j] == 0)		// Empty spaces.
				candi.push_back(make_pair(i, j));
			else if (map[i][j] == 2)		// Virus location.
				virus.push_back(make_pair(i, j));
		}
	}

	DFS(0, 0);		// Exhuasitve search.

	cout << answer << endl;		// Output.
}