#include<iostream>
#include<vector>

#define MAX 13

using namespace std;

const int dy[5] = { 0,0,0,-1,1 };
const int dx[5] = { 0,1,-1,0,0 };

struct position		// The data of knight.
{
	int y, x;			// location.
	int dir;			// direction.
};

int N, K;									// N = The size of mpa.			K = The number of knights.
int map[MAX][MAX];				// map = The memory of input data.
vector<int> cnt[MAX][MAX];	// cnt = The number of knights on the board.
vector<position> vc;				// vc = The memory of knights.

bool Range(int y, int x)		// To figure out the overflow or not.
{
	if (y<1 || y>N || x<1 || x>N)	// Overflow.
		return false;
	return true;
}

bool Check()		// To figure out there is stacked knight or not.
{
	for (int i = 0; i < K; i++)
	{
		if (cnt[vc[i].y][vc[i].x].size() >= 4)		// Stack 4.
			return true;
	}
	return false;
}

void White(int y, int x, vector<int> stk)	// Move to next location with all of knights as stack.
{
	for (int i = 0; i < stk.size(); i++)
	{
		cnt[y][x].push_back(stk[i]);
		vc[stk[i]].y = y;
		vc[stk[i]].x = x;
	}
}

void Red(int y, int x, vector<int> stk)		// Move to next location with all of knights as stack.
{
	for (int i = stk.size() - 1; i >= 0; i--)		// Reverse the sequence.
	{
		cnt[y][x].push_back(stk[i]);
		vc[stk[i]].y = y;
		vc[stk[i]].x = x;
	}
}

void Blue(int y, int x, vector<int> stk, int idx)		// Move to next location with all of knights as stack.
{
	y -= dy[vc[idx].dir];
	x -= dx[vc[idx].dir];
	if (vc[idx].dir == 1)				// Reverse the direction.
		vc[idx].dir = 2;
	else if (vc[idx].dir == 2)
		vc[idx].dir = 1;
	else if (vc[idx].dir == 3)
		vc[idx].dir = 4;
	else
		vc[idx].dir = 3;

	y += dy[vc[idx].dir];		// Move one step.
	x += dx[vc[idx].dir];
	if (!Range(y, x) || map[y][x] == 2)	// Overflow. + Blue.
	{
		y -= dy[vc[idx].dir];
		x -= dx[vc[idx].dir];
		for (int i = 0; i < stk.size(); i++)
		{
			cnt[y][x].push_back(stk[i]);
			vc[stk[i]].y = y;
			vc[stk[i]].x = x;
		}
	}
	else
	{
		if (map[y][x] == 1)	// Red.
			Red(y, x, stk);
		else						// White.
			White(y, x, stk);
	}
}

int Simulation()
{
	int time = 1;
	while (true)
	{
		if (time > 1000)		// Impossible case.
			break;

		for (int idx = 0; idx < K; idx++)		// The whole of kinghts.
		{												// prev = From zero to current one.
			vector<int>stk, prev;				// stk = From the current to last one.	
			int y = vc[idx].y, x = vc[idx].x;
			bool flag = false;
			for (int s = 0; s < cnt[y][x].size(); s++)
			{
				if (cnt[y][x][s] == idx)		// The current one.
					flag = true;

				if (flag)			// From current To last one.
					stk.push_back(cnt[y][x][s]);
				else				// Previous one.
					prev.push_back(cnt[y][x][s]);
			}
			cnt[y][x].clear();	// To avoid using erase().
			cnt[y][x] = prev;		// Clear and paste.

			int ny = y + dy[vc[idx].dir], nx = x + dx[vc[idx].dir];
			if (!Range(ny, nx) || map[ny][nx] == 2)	// Overflow. + Blue.
				Blue(ny, nx, stk, idx);
		
			else if (map[ny][nx] == 1)	// Red.
				Red(ny, nx, stk);
			
			else		// White.
				White(ny, nx, stk);

			if (Check())				// Base case. [Stack = 4]
				return time;
		}
		time += 1;
	}
	return -1;
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);	cout.tie(0);
	
	cin >> N >> K;
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
			cin >> map[i][j];			// Input map data.
	}

	for (int i = 0; i < K; i++)
	{
		int y, x, d;
		cin >> y >> x >> d;				// Input knight data.
		vc.push_back({ y,x,d });
		cnt[y][x].push_back(i);
	}
	
	cout << Simulation() << endl;	// Output.
}