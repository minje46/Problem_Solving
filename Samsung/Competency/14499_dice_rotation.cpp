#include<iostream>
#include<queue>

#define MAX 21

using namespace std;

const int dy[5] = { 0,0,0,-1,1 };		// [1:Right.]	[2:Left.]
const int dx[5] = { 0,1,-1,0,0 };		// [3:Up]		[4:Down.]

int N, M, R, C, K;			// N = The height of map.		M = The width of map.			R,C = The location of dice.		K = The number of instructions.
int map[MAX][MAX];		// map = The memory of original map data.
int dice[6];						// dice = The memory of dice's each side. [0:Down, 1:Left, 2:Front, 3:Right, 4:Rear, 5:Up]	
queue<int>que;				// que = The memory of dice's movement.

void Print()		// To print the up side of dice.
{
	cout << dice[5] << endl;		
}

void Move()		// To move the dice with instruction.
{
	int y = R, x = C;			// Dice's first location.
	while (!que.empty())	// With all instructions. 
	{
		int cur = que.front();	// Direction to move.
		y += dy[cur];
		x += dx[cur];
		que.pop();

		if (y < 0 || y >= N || x < 0 || x >= M)		// Overflow.
		{
			y -= dy[cur];			// Return to previous one.
			x -= dx[cur];
			continue;
		}

		switch (cur)		// [1:Right, 2:Left, 3:Up, 4:Down.]
		{
		case 1:		// Right.
		{
			int down = dice[0];
			int lf = dice[1];
			int rt = dice[3];
			int up = dice[5];

			dice[0] = rt;
			dice[1] = down;
			dice[3] = up;
			dice[5] = lf;
			break;
		}
		case 2:		// Left.
		{
			int down = dice[0];
			int lf = dice[1];
			int rt = dice[3];
			int up = dice[5];

			dice[0] = lf;
			dice[1] = up;
			dice[3] = down;
			dice[5] = rt;
			break;
		}
		case 3:		// Up.
		{
			int down = dice[0];
			int ft = dice[2];
			int rr = dice[4];
			int up = dice[5];

			dice[0] = rr;
			dice[2] = down;
			dice[4] = up;
			dice[5] = ft;
			break;
		}
		case 4:		// Down.
		{
			int down = dice[0];
			int ft = dice[2];
			int rr = dice[4];
			int up = dice[5];

			dice[0] = ft;
			dice[2] = up;
			dice[4] = down;
			dice[5] = rr;
			break;
		}
		default:
			break;
		}

		if (map[y][x] != 0)		
		{
			dice[0] = map[y][x];
			map[y][x] = 0;
		}
		else
			map[y][x] = dice[0];
	
		Print();		// To check the up side of dice every time.
	}
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> N >> M >> R >> C >> K;		// Base input.
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
			cin >> map[i][j];					// Map data.
	}

	for (int i = 0; i < K; i++)
	{
		int d;
		cin >> d;	
		que.push(d);								// Intructions.
	}

	Move();											// Simulation.
}