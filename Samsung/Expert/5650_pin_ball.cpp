#include<iostream>
#include<algorithm>
#include<memory.h>
#include<vector>
//#pragma warning(disable:4996)

#define MAX 101

using namespace std;

int N;			// N = The size of map.
int map[MAX][MAX];					// map = The memory of original input data.
int dy[4] = { -1,0,1,0 };				// [0 : Up.]		[1 : Left.]
int dx[4] = { 0,-1,0,1 };				// [2 : Down.]	[3 : Right.]
vector<pair<int, int>> cand;			// cand = The memory of start location candidates.
vector<pair<int, int>>worm[11];	// worm = The memory of worm hole location to control matched one.
int dup[11];								// dup = The memory of counting worm hole used to avoid loop.
pair<int, int> start;						// start = The location of departure point.

int Convert(int dir)		// To figure out the opposite index.
{
	return (dir + 2) % 4;			// To use this condition, allocate directions differently.
}

int Pin_ball(int dir)		// To do pin ball game based on given rules.
{
	int cnt = 0;				// Count the number of crush.
	int ny = start.first;	// Base state.
	int nx = start.second;
	memset(dup, 0, sizeof(dup));		// Initialization.

	while (true)
	{
		ny += dy[dir];		// Move.
		nx += dx[dir];

		if (ny < 0 || ny >= N || nx < 0 || nx >= N || map[ny][nx] == 5)		// Wall. + Square.
		{
			dir = Convert(dir);		// [Convert the direction as opposite way.]
			cnt++;					// Count the number of crush.
			continue;
		}

		if (map[ny][nx] >= 1 && map[ny][nx] <= 4)		// Splited square.
		{
			switch (map[ny][nx])
			{
			case 1:
			{
				if (dir == 2)		// Go down.
					dir = 3;		// Turn to right.		
				else if (dir == 1)		// Go left.
					dir = 0;				// Turn to up.
				else
					dir = Convert(dir);
				break;
			}
			case 2:
			{
				if (dir == 0)		// Go up.
					dir = 3;		// Turn to right.		
				else if (dir == 1)		// Go left.
					dir = 2;				// Turn to down.
				else
					dir = Convert(dir);
				break;
			}
			case 3:
			{
				if (dir == 0)		// Go up.
					dir = 1;		// Turn to left.		
				else if (dir == 3)		// Go right.
					dir = 2;				// Turn to down.
				else
					dir = Convert(dir);
				break;
			}
			case 4:
			{
				if (dir == 2)		// Go down.
					dir = 1;		// Turn to left.		
				else if (dir == 3)		// Go right.
					dir = 0;				// Turn to up.
				else
					dir = Convert(dir);
				break;
			}
			default:
				break;
			}
			cnt++;
			continue;
		}

		if (map[ny][nx] >= 6 && map[ny][nx] <= 10)		// Worm hole.
		{
			int idx = map[ny][nx];
			dup[idx]++;		// Count the number of worm hole used to avoid loop.
			if (dup[idx] > MAX)		// The condition for avoiding loop.
				return 0;

			for (int i = 0; i < worm[idx].size(); i++)
			{
				if (worm[idx][i].first == ny && worm[idx][i].second == nx)		// To avoid the current coordinates.
					continue;

				ny = worm[idx][i].first;			// Change another way of worm hole.
				nx = worm[idx][i].second;
				break;			// After converted, finish the loop. To avoid repeative compare in wrong way.
			}
			continue;
		}

		if ((ny == start.first && nx == start.second) || map[ny][nx] == -1)		// Return to start position. + Black hole.
			break;
	}
	return cnt;
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);

//	freopen("input.txt", "r", stdin);

	int test_case;
	cin >> test_case;
	for (int t = 1; t <= test_case; t++)
	{	// Initialization.
		memset(map, 0, sizeof(map));
		cand.clear();
		for (int i = 6; i < 11; i++)
			worm[i].clear();

		cin >> N;
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				cin >> map[i][j];		// The original input.

				if (map[i][j] == 0)		// The candidate of start positions.
					cand.push_back(make_pair(i, j));

				if (map[i][j] >= 6 && map[i][j] <= 10)		// The worm hole location.
					worm[map[i][j]].push_back(make_pair(i, j));
			}
		}

		int answer = 0;
		for (int i = 0; i < cand.size(); i++)	// Search the whole of start candidates.
		{
			start.first = cand[i].first;
			start.second = cand[i].second;
			for (int j = 0; j < 4; j++)			// Search the four directions.
				answer = max(answer, Pin_ball(j));
		}

		cout << "#" << t << " " << answer << endl;
	}
}