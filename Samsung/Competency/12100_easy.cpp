#include<iostream>
#include<algorithm>
#include<memory.h>
#include<queue>

#define MAX_N 21
#define MAX_M 6

using namespace std;

const int dy[4] = { -1,1,0,0 };
const int dx[4] = { 0,0,-1,1 };

int N;													// N = The size of map.
int map[MAX_M][MAX_N][MAX_N];		// map = The memory of original input data.
bool visit[MAX_N][MAX_N];					// visit = The memory of visited or not.
int answer = 0;									// answer = The memory of the maximum value on the board as output.	

void Copied(int dpt, int dst)		// To copy the previous map to the next map.
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)	// From departure	
			map[dst][i][j] = map[dpt][i][j];		// To destination.
	}
}

int Pick()		// To choose the maxium value on the board.
{
	int val = 0;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)		// Only one the biggest one.
			val = max(val, map[MAX_M - 1][i][j]);
	}
	return val;
}

void Move(int idx, int dir)		// To move the board in the current direction.
{
	memset(visit, false, sizeof(visit));		// Initialization.
	int y, x;			
	if (dir == 0)		// Up.
	{
		for (int j = 0; j < N; j++)			// The first row and column will be first.
		{
			queue<int> que;
			for (int i = 0; i < N; i++)		// Each column.
			{
				if (map[idx][i][j] != 0)	// If there is another block on the board,
					que.push(map[idx][i][j]);	// push the block in queue.
				map[idx][i][j] = 0;			// Make empty.
			}

			y = 0;			// The index to put the block on the board in a sequence.
			while (!que.empty())
			{
				int cur = que.front();	// In a sequence.
				que.pop();

				if (map[idx][y][j] == 0)	// If the space is empty,
					map[idx][y][j] = cur;	// Just put.

				else								// If not, consider the value of block.
				{
					if (map[idx][y][j] == cur && !visit[y][j])		// Same value + Not combined yet.
					{
						map[idx][y][j] += cur;	// Combine the value.
						visit[y++][j] = true;			// Check it was combined.
					}
					else							// Different value,
						map[idx][++y][j] = cur;	// Just put in next row.
				}
			}
		}
	}

	else if (dir == 1)		// Down.
	{
		for (int j = 0; j < N; j++)				// The last row and first column will be first.
		{
			queue<int> que;
			for (int i = N - 1; i >= 0; i--)			// Each column.
			{
				if (map[idx][i][j] != 0)			// If there is another block on the board,
					que.push(map[idx][i][j]);	// push the block in queue.
				map[idx][i][j] = 0;					// Make empty.
			}

			y = N - 1;			// The index to put the block on the board in a sequence.
			while (!que.empty())
			{
				int cur = que.front();		// In a sequence.
				que.pop();

				if (map[idx][y][j] == 0)	// If the space is empty,
					map[idx][y][j] = cur;	// Just put.

				else								// If not, consider the value of block.
				{
					if (map[idx][y][j] == cur && !visit[y][j])	// Same value + Not combined yet.
					{
						map[idx][y][j] += cur;	// Combine the value.
						visit[y--][j] = true;			// Check it was combined.
					}
					else									// Different value,
						map[idx][--y][j] = cur;	// Just put in next row.
				}
			}
		}
	}

	else if (dir == 2)		// Left.
	{
		for (int i = 0; i < N; i++)			// The first row and first column will be first.
		{
			queue<int> que;
			for (int j = 0; j < N; j++)		// Each row.
			{
				if (map[idx][i][j] != 0)			// If there is another block on the board,
					que.push(map[idx][i][j]);	// push the block in queue.
				map[idx][i][j] = 0;					// Make empty.
			}

			x = 0;				// The index to put the block on the board in a sequence.
			while (!que.empty())
			{
				int cur = que.front();		// In a sequence.
				que.pop();

				if (map[idx][i][x] == 0)	// If the space is empty,
					map[idx][i][x] = cur;	// Just put.

				else								// If not, consider the value of block.
				{
					if (map[idx][i][x] == cur && !visit[i][x])		// Same value + Not combined yet.
					{
						map[idx][i][x] += cur;	// Combine the value.
						visit[i][x++] = true;			// Check it was combined.
					}
					else					// Different value,
						map[idx][i][++x] = cur;	// Just put in next row.
				}
			}
		}
	}

	else if (dir == 3)		// Right.
	{
		for (int i = 0; i < N; i++)					// The last row and first column will be first.
		{
			queue<int> que;
			for (int j = N - 1; j >= 0; j--)			// Each row.
			{
				if (map[idx][i][j] != 0)			// If there is another block on the board,
					que.push(map[idx][i][j]);	// push the block in queue.
				map[idx][i][j] = 0;					// Make empty.
			}

			x = N-1;			// The index to put the block on the board in a sequence.
			while (!que.empty())
			{
				int cur = que.front();		// In a sequence.
				que.pop();

				if (map[idx][i][x] == 0)	// If the space is empty,
					map[idx][i][x] = cur;	// Just put.

				else			// If not, consider the value of block.
				{
					if (map[idx][i][x] == cur && !visit[i][x])		// Same value + Not combined yet.
					{
						map[idx][i][x] += cur;	// Combine the value.
						visit[i][x--] = true;			// Check it was combined.
					}
					else		// Different value,
						map[idx][i][--x] = cur;	// Just put in next row.
				}
			}
		}
	}
}

void DFS(int cnt)		// To do exhaustive search the movement by all kinds of direction.
{
	if (cnt == MAX_M - 1)		// Base case.
	{									
		answer = max(answer, Pick());		// Compare the maximum value on the board.
		return;
	}

	for (int i = 0; i < 4; i++)	// Four directions.
	{									// Up, Down, Left, Right.
		Copied(cnt, cnt + 1);	// Copy the current map.	
		Move(cnt + 1, i);			// Move to i'th direction.
		DFS(cnt + 1);				// DFS.
	}
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> N;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
			cin >> map[0][i][j];		// The original map data.
	}

	DFS(0);		// Exhaustive search.

	cout << answer << endl;			// Output.
}