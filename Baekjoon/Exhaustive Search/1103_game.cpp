#include<iostream>
#include<algorithm>
#include<memory.h>

#define MAX 51

using namespace std;

const int dy[4] = { -1,1,0,0 };
const int dx[4] = { 0,0,-1,1 };

int N, M;							// N = The height of map.				M = The width of map.
char map[MAX][MAX];	// map = The memory of input data.
int cache[MAX][MAX];	// cache = The memory of memoization.	
bool visit[MAX][MAX];		// visit = The memory of visited or not.

int DFS(int y, int x)			// To figure out the whole of movement.
{
	if (y < 0 || y >= N || x < 0 || x >= M || map[y][x] == 'H')	// Base case. [Oveflow.]
		return 0;

	if (visit[y][x])		// Already visited.
	{						// Infinite loop.
		cout << -1 << endl;	
		exit(0);
	}

	if (cache[y][x])		// Already memoized.
		return cache[y][x];		// Using previous value.
	
	visit[y][x] = true;
	for (int i = 0; i < 4; i++)
	{
		int val = map[y][x] - '0';
		int ny = y + (dy[i] * val);
		int nx = x + (dx[i] * val);
		cache[y][x] = max(cache[y][x], DFS(ny, nx) + 1);		// Recursive search.
	}																				// And add +1 after returned to original one.
	visit[y][x] = false;

	return cache[y][x];
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);	cout.tie(0);

	cin >> N >> M;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
			cin >> map[i][j];			// Input.
	}

	cout << DFS(0, 0) << endl;		// Output.
}