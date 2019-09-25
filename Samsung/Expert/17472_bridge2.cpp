#include<iostream>
#include<algorithm>
#include<memory.h>
#include<vector>
#include<queue>

#define MAX 11
#define ISLAND 7
#define INF 987654321

using namespace std;

const int dy[4] = { -1,1,0,0 };
const int dx[4] = { 0,0,-1,1 };

struct Bridge		// The bridge data.
{
	pair<int, int> dpt, dst;		// Departure, Destination.
	int len;			// The length of bridge.
	bool used;		// Used or not for combination.
};

int N, M;							// N = The height of map.			M = The width of map.
int map[MAX][MAX];		// map = The memory of original map.
bool visit[MAX][MAX];		// visit = The memory of whether it is visited or not.
vector<Bridge> bridge;		// bridge = The memory of bridges.
bool check[ISLAND];		// check = The memory of whether the current bridges makes MST or not.
int num = 1, answer = INF;		// num = The number of islands.			answer = The shortest total length of bridges.

bool Range(int y, int x)		// To figure out this location is possible or not.
{
	if (y < 0 || y >= N || x < 0 || x >= M)	// Overflow.
		return false;
	return true;
}

bool Find(pair<int, int> start, pair<int, int> end)		// To figure out the same bridge is or not.
{
	for (int i = 0; i < bridge.size(); i++)
	{
		if (bridge[i].dpt == end && bridge[i].dst == start)	// [a->b] == [b->a] are same bridge.
			return false;													// That's why compare (dpt, end) and (dst, start).
	}
	return true;
}

int Count()		// To count the total length of bridges.
{
	int tot = 0;
	for (int i = 0; i < bridge.size(); i++)
	{
		if (!bridge[i].used)			// Consider the used bridge only.
			tot += bridge[i].len;	
	}
	return tot;
}

void Arrive(int cur)		// To figure out MST or Not.
{
	if (check[cur])		// Base case. [Already visited, pass.]
		return;

	check[cur] = true;	// Visited.
	for (int i = 0; i < bridge.size(); i++)
	{
		if (!bridge[i].used)		// Possible to use.
		{
			int start = map[bridge[i].dpt.first][bridge[i].dpt.second];
			int end = map[bridge[i].dst.first][bridge[i].dst.second];

			if (cur == start)	// From current,
				Arrive(end);	// to destination.
			if (cur == end)		
				Arrive(start);
		}
	}
}

bool Possible()		// To figure out all of islands could move to others.
{
	for (int k = 1; k < num; k++)		// From 1 to last island.
	{
		memset(check, false, sizeof(check));	// Initialzation.
		Arrive(k);		// DFS.
		for (int i = 1; i < num; i++)
		{
			if (!check[i])		// If there is island not to move,
				return false;	// Fail.
		}
	}
	return true;
}

void BFS(int y, int x, int num)		// To make the isalnd group based on bfs.
{
	queue<pair<int, int>>que;
	que.push(make_pair(y, x));		// From the departure position.

	while (!que.empty())
	{
		auto cur = que.front();
		que.pop();

		visit[cur.first][cur.second] = true;			
		map[cur.first][cur.second] = num;		// Make same group.

		for (int i = 0; i < 4; i++)
		{
			int ny = cur.first + dy[i];
			int nx = cur.second + dx[i];

			if (!Range(ny, nx))		// Overflow.
				continue;

			if (!visit[ny][nx] && map[ny][nx] != 0)		// Not visited yet. + Continent.
				que.push(make_pair(ny, nx));
		}
	}
}

void Connected(int y, int x)		// To build the bridge from (y,x) location.
{
	for (int dir = 0; dir < 4; dir++)	// Four directions.
	{
		int ny = y + dy[dir];
		int nx = x + dx[dir];
		int len = 0;

		while (Range(ny, nx))		// Not over flow.
		{
			if (map[ny][nx] > 0)	// If the bridges arrive at other continent,
			{
				if (len >= 2 && Find({ y,x }, { ny,nx }))		// and it has longer than length(2). + No duplication.
					bridge.push_back({ {y,x}, {ny,nx}, len, false });		// [dpt, dst, length, used].
				break;
			}
			ny += dy[dir];		// Move to (y,x) coordinates.	
			nx += dx[dir];
			len += 1;			// Increase the length of bridge.
		}		
	}
}

void DFS(int idx, int cnt, int target)		// To check all of combination cases.
{	// (The current index of bridge, The selected number of bridges to use, The total number of bridges to use.]								
	if (cnt == target)		// Base case. [The number of bridges to use.]
	{
		if (Possible())		// MST or not.
			answer = min(answer, Count());	// Compare the shortest length.
		return;
	}

	if (idx >= bridge.size())		// Over flow.
		return;
	// Combination.
	bridge[idx].used = true;	
	DFS(idx + 1, cnt + 1, target);
	bridge[idx].used = false;
	DFS(idx + 1, cnt, target);
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> N >> M;						// Map size.		
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
			cin >> map[i][j];			// Input of map.
	}

	memset(visit, false, sizeof(visit));		// Initialization.
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			if (map[i][j] != 0 && !visit[i][j])		// Continent + Not visited yet.
				BFS(i, j, num++);						// Make a island group.
		}
	}

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			if (map[i][j] > 0)		// Continent.
				Connected(i, j);		// Build the bridges. 
		}
	}

	for (int i = 0; i < bridge.size(); i++)		// The number of bridges to use.
		DFS(0, 0, i);								// To figure out all of combinations.		

	if (answer == INF)				// Impossible to connect MST.
		answer = -1;
	cout << answer << endl;		// Output.
}