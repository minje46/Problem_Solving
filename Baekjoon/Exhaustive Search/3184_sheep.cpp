#include<iostream>
#include<memory.h>
#include<queue>

#define MAX 251

using namespace std;

const int dy[4] = { -1,1,0,0 };
const int dx[4] = { 0,0,-1,1 };

int R, C;								// R = The height of map.			C = The width of map.
char map[MAX][MAX];		// map = The memory of input data.	
bool visit[MAX][MAX];			// visit = The memory of visited or not.
int survive[2];						// survive = The number of sheep and wolf as output. 

pair<int, int> BFS(int y, int x)		// To figure out the area and number of sheep and wolves.
{
	pair<int, int> cnt = { 0,0 };		// The number of sheep and wolf.
												// [0] : sheep.		[1] : wolf.
	queue<pair<int, int>>que;
	que.push(make_pair(y, x));
	visit[y][x] = true;
	while (!que.empty())
	{
		auto cur = que.front();
		que.pop();

		if (map[cur.first][cur.second] == 'o')		// Sheep.
			cnt.first += 1;			// Count.
		else if (map[cur.first][cur.second] == 'v')	// Wolf.
			cnt.second += 1;		// Count.

		for (int i = 0; i < 4; i++)
		{
			int ny = cur.first + dy[i];
			int nx = cur.second + dx[i];

			if (ny < 0 || ny >= R || nx < 0 || nx >= C)		// Overflow.
				continue;

			if (!visit[ny][nx] && map[ny][nx] != '#')		// Not visit yet. + Not fence.
			{
				que.push(make_pair(ny, nx));
				visit[ny][nx] = true;
			}
		}
	}
	return cnt;
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);	cout.tie(0);
	memset(visit, false, sizeof(visit));
	cin >> R >> C;						// Size of map.
	for (int i = 0; i < R; i++)
	{
		for (int j = 0; j < C; j++)	
			cin >> map[i][j];			// Input data.
	}

	for (int i = 0; i < R; i++)
	{
		for (int j = 0; j < C; j++)
		{
			if (!visit[i][j] && map[i][j] != '#')		// Not visit yet.	+ Not fence.
			{
				pair<int, int> cnt = BFS(i, j);			// To figure out the area.	

				if (cnt.first > cnt.second)				// Sheep is more than wolf.
					cnt.second = 0;						// wolf die.	
				else											// Wolf is more than sheep.
					cnt.first = 0;							// sheep die.
				survive[0] += cnt.first;					// [0] : Sheep.
				survive[1] += cnt.second;			// [1] : Wolf.	
			}
		}
	}

	cout << survive[0] << " " << survive[1] << endl;		// Output.
}