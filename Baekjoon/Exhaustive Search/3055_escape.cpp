#include<iostream>
#include<algorithm>
#include<memory.h>
#include<queue>

#define MAX 50
#define INF 987654321

using namespace std;

const int dy[4] = { -1,1,0,0 };
const int dx[4] = { 0,0,-1,1 };

struct Move	// The data structure for bfs.
{
	int y, x;		// Coordinate.
	int time;		// Time.
};

int N, M;			// N = The height of map.			M = The width of map.
char map[MAX][MAX];		// map = The memory of original input data.
int water[MAX][MAX];			// water = The memory of water flooded with time.
pair<int, int> dpt, dst;			// dpt, dst = The memory of departure and destination location.
int answer = INF;					// answer = The minimum time to arrive destination as output.

bool Range(int y, int x)			// To figure out whether it is overflow or not.
{
	if (y < 0 || y >= N || x < 0 || x >= M)	// Overflow.
		return false;
	return true;
}

void Flood()		// To figure out the water movement time by time.
{
	bool visit[MAX][MAX];			// The temporary memory to avoid duplicate visited.
	memset(visit, false, sizeof(visit));

	queue<Move>que;	
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			if (map[i][j] == '*')			// To find the base water location.
			{
				que.push({ i,j,0 });
				visit[i][j] = true;			
			}
		}
	}
	
	while (!que.empty())		// Until there is no more possible area.
	{
		auto cur = que.front();		// The current data.
		que.pop();	

		water[cur.y][cur.x] = cur.time;		// The time of flooded.
		for (int i = 0; i < 4; i++)
		{
			int ny = cur.y + dy[i];	// Next coordinate.
			int nx = cur.x + dx[i];

			if (!Range(ny, nx) || visit[ny][nx])	// Overflow.
				continue;

			if (map[ny][nx] == '.')		// Water could move to empty space only.
			{
				que.push({ ny,nx,cur.time + 1 });		
				visit[ny][nx] = true;		// Visit check to avoid duplicate. [It is the main factor of memory overused.]
			}
		}
	}
}

void BFS()		// To figure out the hedgehog's movement.
{
	bool visit[MAX][MAX];			// The temporary memory to avoid duplicate visited.
	memset(visit, false, sizeof(visit));

	queue<Move>que;
	que.push({ dpt.first, dpt.second, 0 });		// The departure location.
	visit[dpt.first][dpt.second] = true;
	while (!que.empty())		// Until there is no more possible area.
	{
		auto cur = que.front();		// The current data.
		que.pop();

		if (cur.y == dst.first && cur.x == dst.second)		// Destination.
		{
			answer = min(answer, cur.time);
			return;
		}

		for (int i = 0; i < 4; i++)
		{
			int ny = cur.y + dy[i];	// Next coordinate.
			int nx = cur.x + dx[i];

			if (!Range(ny, nx) || visit[ny][nx])	// Overflow.
				continue;

			if ((map[ny][nx] == '.' && (water[ny][nx] == 0 || water[ny][nx] > cur.time + 1)) || map[ny][nx] == 'D')
			{	// Empty space + Not flooded yet. || Destination.
				que.push({ ny,nx,cur.time + 1 });
				visit[ny][nx] = true;		// Visit check to avoid duplicate. [It is the main factor of memory overused.]
			}
		}
	}
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> N >> M;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			cin >> map[i][j];			// Input.
			if (map[i][j] == 'S')			// Departure.
				dpt = { i,j };
			else if (map[i][j] == 'D')	// Destination.	
				dst = { i,j };
		}
	}

	Flood();		// Flooded.
	BFS();		// bfs algoritm.

	if (answer == INF)		// Impossible.
		cout << "KAKTUS" << endl;
	else							// Possible.
		cout << answer << endl;
}