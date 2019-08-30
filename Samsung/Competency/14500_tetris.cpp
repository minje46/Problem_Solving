#include<iostream>
#include<algorithm>

#define MAX 501

using namespace std;

const int dy[4] = { -1,1,0,0 };		// Up, Down.
const int dx[4] = { 0,0,-1,1 };		// Left, Right.
const int poly[4][3][2] = {			// Special figure block.
	{ { 0,1 },{ 0,2 },{ 1,1 } },		// 'ぬ'
{ { 0,1 },{ 0,2 },{ -1,1 } },			// 'で'
{ { 1,0 },{ 2,0 },{ 1,1 } },			// 'た'
{ { 1,0 },{ 2,0 },{ 1,-1 } }			// 'っ'
};

int N, M;							// N = The height of map.			M = The width of map.
int map[MAX][MAX];		//	map = The memory of original map data.
bool visit[MAX][MAX];		// visit = The memory of visited or not.
int answer = 0;				// answer = The maximum sum value as output.

bool Range(int y, int x)		// To check (y,x) location is proper or not.
{
	if (y < 0 || y >= N || x < 0 || x >= M)	// Overflow.
		return false;

	return true;
}

void Poly(int y, int x)		// To check special figure block.
{
	for (int k = 0; k < 4; k++)		// In four directions.
	{
		int tot = map[y][x];
		int cnt = 1;
		for (int r = 0; r < 3; r++)
		{
			int ny = y + poly[k][r][0];
			int nx = x + poly[k][r][1];

			if (!Range(ny, nx))		// Is proper range or not.
				continue;

			tot += map[ny][nx];
			cnt++;
		}
		if (cnt == 4)			// Possible to check all directions.
			answer = max(answer, tot);	
	}
}

void DFS(int y, int x, int cnt, int tot)		// To do exhaustive search with permutations.
{
	if (cnt == 4)		// Base case. [Tetris.]
	{
		answer = max(answer, tot);		// Compare the maximum sum value.
		return;
	}

	for (int i = 0; i < 4; i++)	// To check four directions.
	{
		int ny = y + dy[i];
		int nx = x + dx[i];

		if(!Range(ny, nx))		// Is proper range or not.
			continue;

		if (!visit[ny][nx])			// To avoid duplicate visited.
		{
			visit[ny][nx] = true;	
			DFS(ny, nx, cnt + 1, tot + map[ny][nx]);		// Permutation.
			visit[ny][nx] = false;
		}
	}
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> N >> M;						// Map data.
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
			cin >> map[i][j];			// Original input data.
	}

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			visit[i][j] = true;
			DFS(i, j, 1, map[i][j]);	// Four blocks with permutation.	
			Poly(i, j);						// Special figure.
			visit[i][j] = false;
		}
	}

	cout << answer << endl;			// Output.
}