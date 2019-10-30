#include<iostream>
#include<memory.h>
#include<queue>
#pragma warning(disable:4996)

#define MAX 16

using namespace std;

const int dy[4] = { -1,1,0,0 };
const int dx[4] = { 0,0,-1,1 };

char map[MAX][MAX];		// map = The memory of input data.
bool visit[MAX][MAX];			// visit = The memory of visited or not.
pair<int, int> dpt, dst;			// dpt, dst = The location of departure and destination.

bool BFS()			// To figure out the whole of cases to escape.
{
	queue<pair<int, int>> que;
	que.push(make_pair(dpt.first, dpt.second));		// Departure.
	visit[dpt.first][dpt.second] = true;
	while (!que.empty())
	{
		auto cur = que.front();
		que.pop();

		for (int i = 0; i < 4; i++)
		{
			int ny = cur.first + dy[i];
			int nx = cur.second + dx[i];

			if (ny < 0 || ny >= MAX || nx < 0 || nx >= MAX)		// Overflow.
				continue;

			if (ny== dst.first && nx == dst.second)		// Destination.
				return true;

			if (!visit[ny][nx] && map[ny][nx] == '0')	// Not visit yet. + Aisle.
			{
				visit[ny][nx] = true;
				que.push(make_pair(ny, nx));
			}
		}
	}
	return false;
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);	cout.tie(0);

	//freopen("input.txt", "r", stdin);
	for (int t = 1; t <= 10; t++)
	{
		int test_case;
		cin >> test_case;
		for (int i = 0; i < MAX; i++)
		{
			for (int j = 0; j < MAX; j++)
			{
				cin >> map[i][j];			// Input.
				if (map[i][j] == '2')			// Departure.
					dpt = { i,j };
				else if (map[i][j] == '3')	// Destination.	
					dst = { i,j };
			}
		}

		memset(visit, false, sizeof(visit));		// Initialization.
		cout << "#" << test_case << " " << BFS() << endl;		// Output.
	}
}