#include<iostream>
#include<algorithm>
#include<memory.h>
#include<queue>
//#pragma warning(disable:4996)

#define MAX 51

using namespace std;

const int dy[4] = { 0,-1,0,1 };		// Left, Up.
const int dx[4] = { -1,0,1,0 };		// Right, Down.
const int pipe[8][4] =					// pipe = It shows which direction is opened. 
{						// [Left, Up, Right, Down.] -> To calculate opposite direction easily. 
	{ 0,0,0,0 },		// Pipe 0 : None.
{ 1,1,1,1 },		// Pipe 1 : Up, Down, Left, Right.
{ 0,1,0,1 },		// Pipe 2 : Up, Down.
{ 1,0,1,0 },		// Pipe 3 : Left, Right.
{ 0,1,1,0 },		// Pipe 4 : Up, Right.
{ 0,0,1,1 },		// Pipe 5 : Down, Right.
{ 1,0,0,1 },		// Pipe 6 : Down, Left.
{ 1,1,0,0 }		// Pipe 7 : Up, Left.
};

struct Runner		// Runner = The memory of fugitive.
{
	int y, x;			// Location.
	int time;			// Time to spend.
};

int N, M, L, R, C;			// N = The height of map.	M = The width of map.		L = The time to run away.		R,C = The location of fugitive.
int map[MAX][MAX];		// map = The memory of original map data.
bool visit[MAX][MAX];		// visit = The memory of visited or not.

bool Check(int ny, int nx, int nt, int idx)		// To figure out wheter new location(ny,nx) is proper to move or not.
{
	if (ny < 0 || ny >= N || nx < 0 || nx >= M)		// Overflow.
		return false;

	int dst = (idx + 2) % 4;		// To calculate opposite direction.
	if (visit[ny][nx] || map[ny][nx] == 0 || !pipe[nt][dst])		// Already visited. + Wall space. + Closed pipe.
		return false;

	return true;
}

void Move()		// To move fugitive as time flows.
{
	queue<Runner>que;		// que = The memory for BFS searching.
	que.push({ R,C,0 });		// Location(y,x). + Time.

	while (!que.empty())
	{
		auto cur = que.front();
		que.pop();

		if (cur.time == L)		// Base case. [Time limit.]
			continue;

		visit[cur.y][cur.x] = true;		// Possible to visit.

		int type = map[cur.y][cur.x];	// Tunnel type.
		for (int i = 0; i < 4; i++)
		{
			if (pipe[type][i])			// [현재 Pipe에서 open 된 방향만 확인하면됨.]
			{	// New location's data.
				int ny = cur.y + dy[i];
				int nx = cur.x + dx[i];
				int nt = map[ny][nx];

				if (Check(ny, nx, nt, i))		// To check wheter new location(ny,nx) is proper to move or not.
					que.push({ ny,nx,cur.time + 1 });		// Possible case.
			}
		}
	}
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	//freopen("input.txt", "r", stdin);

	int test_case;
	cin >> test_case;
	for (int t = 1; t <= test_case; t++)
	{	// Initialization.
		memset(map, 0, sizeof(map));
		memset(visit, false, sizeof(visit));

		cin >> N >> M >> R >> C >> L;
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < M; j++)
				cin >> map[i][j];
		}

		visit[R][C] = true;
		Move();		// Location(R,C), Time, Prev.

		int answer = 0;		// answer = The total number of possible escape space.
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < M; j++)
			{
				if (visit[i][j])
					answer++;
			}
		}

		cout << "#" << t << " " << answer << endl;
	}
}