#include<iostream>
#include<algorithm>
#include<vector>

#define MAX 51

using namespace std;

int N, M;									// N = The height of map.			M = The width of map.
int map[MAX][MAX];				// map = The memory of map.
int answer = 0;						// answer = The number of cleaned.
// Forward way.
int dy[4] = { -1, 0, 1, 0 };		// [0] = North.		[1] = East.
int dx[4] = { 0, 1, 0, -1 };		// [2] = South.		[3] = West.
// Backward way.	
int by[4] = { 1, 0, -1, 0 };		// [0] = Do rear with north direction. [Move to south in real.]		[1] = Do rear with east direction. [Move to west in real.]		
int bx[4] = { 0, -1, 0, 1 };		// [2] = Do rear with south direction. [Move to north in real.]		[3] = Do rear with west direction. [Move to east in real.]

void Clean(int y, int x, int dir)	// To figure out that it is possible to clean on this coordinate with direction.
{											// [Direction과 함께, (y,x) 좌표가 청소 가능한지 판단.]
	if (map[y][x] == 1)				// The base condition.
		return;							// There is no way to move. (The [1] means wall.)

	if (map[y][x] == 0)		// If this area is able to be cleaned.
	{
		map[y][x] = -1;		// Clean the current location. (The [-1] means cleaned.)
		answer++;				// Count the number of cleaned.
	}

	for (int i = 0; i < 4; i++)
	{
		int ndir = dir - 1 < 0 ? 3 : dir - 1;		// [North->West.]	[East->North.]	[South->East.]	[West->South.]
		int ny = y + dy[ndir];		// (ny, nx) = new coordinate with new direction.
		int nx = x + dx[ndir];		//  Forward directions are stored in (dy,dx) before.

		if (map[ny][nx] == 0)		// If the new area is able to be cleaned.
		{
			Clean(ny, nx, ndir);		// Move to new area.
			return;
		}
		else								// If the new area is wall or was cleaned before.
			dir = ndir;					// Change the direction only.
	}										// [Direction만 바꾸고 loop 실행하여, 상하좌우를 탐색.]

	int ny = y + by[dir];				// (ny, nx) = new coordinate with new direction.
	int nx = x + bx[dir];				//  Backward directions are stored in (by,bx) before.
	Clean(ny, nx, dir);				// Move to rear area with current direction.
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cin >> N >> M;

	int y, x, dir;					// y,x = The coordinate of robot vacuum.		dir = The direction of robot vacuum.
	cin >> y >> x >> dir;

	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			cin >> map[i][j];

	Clean(y, x, dir);			// To figure out that it is possible to clean on this coordinate with direction.

	cout << answer << endl;		// The number of cleaned as output.
}