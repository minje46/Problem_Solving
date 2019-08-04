#include<iostream>
#include<algorithm>
#include<memory.h>
#include<vector>

#define MAX 9
#define INF 987654321

using namespace std;

struct CCTV	// The memory of CCTV data.
{
	int type;		// The type of camera.
	int y, x;		// Location.
};

int N, M;					// N = The height of map.		M = The width of map.	
int map[MAX][MAX];		// map = The memory of original map.
int visit[MAX][MAX];		// visit = The memory of visited or not. 	
int dy[4] = { -1, 1, 0, 0 };		// Up, Down.
int dx[4] = { 0, 0, -1, 1 };		// Left, Right.
vector<CCTV>ct;			// ct = The location of each cctv.
int answer = INF;			// answer = The number of blind spots.

int Count()		// To count blind spots.
{
	int cnt = 0;
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= M; j++)
			if (visit[i][j] == -1 && map[i][j] == 0)		// [visit == -1] is blind spot. + [map == 0] is empty space.	
				cnt++;
	}
	return cnt;
}

void Turn_on(int y, int x, int dir, int type)		// To turn on the cctv's sight. 
{
	if (y <1 || y >N || x <1 || x>M || map[y][x] == 6)		// Base case. [Overflow.]
		return;

	if (visit[y][x] == -1 && map[y][x] == 0)		// [visit == -1] is not checked yet. + [map == 0] is empty space.	
		visit[y][x] = type;
	Turn_on(y + dy[dir], x + dx[dir], dir, type);		// Recursive search.
}

void Turn_off(int y, int x, int dir, int type)	// To turn off the cctv's sight. 
{
	if (y <1 || y >N || x <1 || x>M || map[y][x] == 6)		// Base case. [Overflow.]
		return;

	if (visit[y][x] == type && map[y][x] == 0)		// [visit == type] is its observance space. + [map == 0] is empty space.	
		visit[y][x] = -1;
	Turn_off(y + dy[dir], x + dx[dir], dir, type);	// Recursive search.	
}

void DFS(int idx)		// To figure out the whole of combinations using backtracking.
{
	if (idx == ct.size())	// It means searching the whole of cctvs. [Base case.]
	{
		answer = min(answer, Count());		// Minimum blind spots.
		return;
	}

	switch (ct[idx].type)	// Depends on cctv's type.
	{
	case 1:		// It can observe only one way. [Up, Down, Left, Right.]
		for (int k = 0; k < 4; k++)
		{
			Turn_on(ct[idx].y, ct[idx].x, k, ct[idx].type*idx*idx + k);		// Turn on the one way.
			DFS(idx + 1);		// Backtracking.
			Turn_off(ct[idx].y, ct[idx].x, k, ct[idx].type * idx*idx + k);	// Return to original state.
		}
		break;

	case 2:		// It can observe opposite ways. [Up, Down. / Left, Right.]
		for (int k = 0; k < 4; k += 2)
		{
			Turn_on(ct[idx].y, ct[idx].x, k, ct[idx].type * idx*idx + k);	// Turn on the first way.
			Turn_on(ct[idx].y, ct[idx].x, k + 1, ct[idx].type * idx*idx + k + 1);		// Turn on the second way.
			DFS(idx + 1);		// Backtracking.
			Turn_off(ct[idx].y, ct[idx].x, k, ct[idx].type * idx*idx + k);	// Return to original state.
			Turn_off(ct[idx].y, ct[idx].x, k + 1, ct[idx].type * idx*idx + k + 1);	// Return to original state.
		}
		break;

	case 3:		// It can observe rectangular ways. 
		for (int k = 0; k < 2; k++)
		{
			for (int h = 2; h < 4; h++)
			{
				Turn_on(ct[idx].y, ct[idx].x, k, ct[idx].type * idx*idx + k);		// Turn on the first way.
				Turn_on(ct[idx].y, ct[idx].x, h, ct[idx].type * idx*idx + h);		// Turn on the second way.
				DFS(idx + 1);		// Backtracking.
				Turn_off(ct[idx].y, ct[idx].x, k, ct[idx].type * idx*idx + k);		// Return to original state.
				Turn_off(ct[idx].y, ct[idx].x, h, ct[idx].type * idx*idx + h);		// Return to original state.
			}
		}
		break;

	case 4:		// It can observe three ways.
		for (int k = 0; k < 4; k++)
		{
			for (int h = 0; h < 4; h++)
			{
				if (k == h)			// Except one way.
					continue;
				Turn_on(ct[idx].y, ct[idx].x, h, ct[idx].type * idx*idx + h);		// Turn on three ways.
			}
			DFS(idx + 1);			// Backtracking.
			for (int h = 0; h < 4; h++)
			{
				if (k == h)
					continue;
				Turn_off(ct[idx].y, ct[idx].x, h, ct[idx].type * idx*idx + h);		// Return to original state.
			}
		}
		break;

	case 5:			// It can observe the whole of ways.
		for (int k = 0; k < 4; k++)
			Turn_on(ct[idx].y, ct[idx].x, k, ct[idx].type * idx *idx + k);		// Turn on all of ways.
		DFS(idx + 1);		// Backtracking.
		break;

	default:
		break;
	}
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	// Initialization.
	memset(map, -1, sizeof(map));
	memset(visit, -1, sizeof(visit));
	cin >> N >> M;
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= M; j++)
		{
			cin >> map[i][j];			// Original map.

			if (map[i][j] != 0 && map[i][j] != 6)		// CCTV location.
			{
				ct.push_back({ map[i][j], i,j });
				visit[i][j] = map[i][j];
			}
		}
	}

	DFS(0);		// ct[0], cnt;

	cout << answer << endl;
}
