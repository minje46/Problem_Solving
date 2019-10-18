#include<iostream>
#include<memory.h>
#include<queue>

#define MAX 101

using namespace std;

const int dy[5] = { 0,0,0,1,-1 };
const int dx[5] = { 0,1,-1,0,0, };

struct location		// The data of location.	
{
	int y, x;		// Coordinate.
	int dir;		// Direction.
	int cnt;		// Distnace to move.
};
	
int N, M;								// N = The height of map.				M = The width of map.
int map[MAX][MAX];			// map = The memory of input data.
bool visit [5][MAX][MAX];	// visit = The memory of visited or not.
location dpt, dst;					// dpt, dst = The memory of departure and destination info.
int answer = 0;					// answer = The minimum way to arrive at destination as output.

bool Range(int y, int x)			// To figure out it is correct range or not.
{
	if (y<1 || y > N || x<1 || x>M)		// Overflow.
		return false;
	return true;
}

void BFS()			// To figure out the shortest way to arrive at destination.
{
	queue<location> que;
	que.push({ dpt.y, dpt.x, dpt.dir, 0 });
	visit[0][dpt.y][dpt.x] = true;
	while (!que.empty())	
	{
		auto cur = que.front();
		que.pop();

		if (cur.y == dst.y && cur.x == dst.x && cur.dir == dst.dir)		// Base case. [Destination.]
		{
			answer = cur.cnt;
			return;
		}

		for (int i =1; i <= 3; i++)		// Go straight.
		{
			int ny = cur.y + (dy[cur.dir] * i);		
			int nx = cur.x + (dx[cur.dir] * i);

			if (visit[cur.dir][ny][nx])		// Already visited.
				continue;

			if (Range(ny, nx) && map[ny][nx] == 0)		// Correct range. + Empty space.
			{
				que.push({ ny,nx,cur.dir,cur.cnt + 1 });
				visit[cur.dir][ny][nx] = true;
			}
			else			// If there is wall or overflow, it doens't need to take care other case.
				break;
		}
		
		for (int i = 1; i <= 4; i++)		// Rotate the direction.
		{
			if (cur.dir != i && !visit[i][cur.y][cur.x])		// Current direction. + Already visited.
			{
				visit[cur.dir][cur.y][cur.x] = true;
				if ((cur.dir == 1 && i == 2) || (cur.dir == 2 && i == 1) || (cur.dir == 3 && i == 4) || (cur.dir == 4 && i == 3))		// Opposite way.
					que.push({ cur.y, cur.x, i, cur.cnt + 2 });
				else							// 90 degree rotation.
					que.push({ cur.y, cur.x, i, cur.cnt + 1 });
			}
		}
	}
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);	cout.tie(0);

	cin >> N >> M;
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= M; j++)
			cin >> map[i][j];				// Input data.
	}
	int y, x, d;
	cin >> y >> x >> d;						// Departure.
	dpt = { y,x,d, 0 };
	cin >> y >> x >> d;						// Destination.
	dst = { y,x,d,0 };

	memset(visit, false, sizeof(visit));	// Initiailization.
	BFS();			// To do exhuastive search.

	cout << answer << endl;				// Output.
}