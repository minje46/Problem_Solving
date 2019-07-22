#include<iostream>
#include<algorithm>

#define MAX 501

using namespace std;

int N;									// N = The size of map.
int map[MAX][MAX];			// The memory of map.
int memo[MAX][MAX];		// The memory of memoization to do dynamic programming.	
int dy[4] = { -1, 1, 0, 0 };	// Up, Down.
int dx[4] = { 0, 0, -1, 1 };	// Left, Right.

int DFS(int y, int x)		// To figure out the maximum day panda can alive.
{	
	if (memo[y][x])		// If the day was stored, it doesn't need to be calculate again.
		return memo[y][x];		// [memoization의 기능이 visit을 check하는 것 처럼, 이미 저장한 day의 value가 있는 경우 재계산을 피한다.]

	memo[y][x] = 1;	// The least condition of map. [Panda가 최소 1일은 살 수 있다. Bamboo map의 어디서든..]

	for (int i = 0; i < 4; i++)	// Up, Down, Left, Right to dfs.
	{
		int ny = y + dy[i];		// The new y coordinate.
		int nx = x + dx[i];		// The new x coordintae.

		if (ny<1 || ny>N || nx<1 || nx >N)	// Overflow area.
			continue;

		if (map[ny][nx] > map[y][x])			// Panda can move new location where it has more bamboo than current location.
			memo[y][x] = max(memo[y][x], DFS(ny, nx) + 1);		// [기존 memoization된 value와 dfs를 통해 파악된 value+1 의 값을 비교.]
	}							// [모든 memoization[y][x] = 1로 저장하기 때문에, 이동이 가능한 경로가 return될 때, +1로 비교하여 저장한다.]

	return memo[y][x];			// The day value in memoization.
}

int main(void)
{
	ios_base::sync_with_stdio(false);

	cin >> N;								// The size of bamboo map.
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++)		// [대나무 숲의 정보.]
			cin >> map[i][j];			// The input data of bamboo map.
	
	int answer = -1;						// answer = The maximum day panda can alive.
	for (int i = 1; i <= N; i++)			// Search all bamboo map.
		for (int j = 1; j <= N; j++)		
			answer = max(answer, DFS(i,j));		// To figure out the day based on bamboo map.
	
	cout << answer << endl;			// The output which is called maximum day to live.
}