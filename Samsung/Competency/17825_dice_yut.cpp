#include<iostream>
#include<algorithm>
#include<vector>

#define DICE 11
#define MAX 26

using namespace std;

struct Knight		// The data of knight.
{
	int y, x;			// Location.
	int score;		// Score.
};

int input[DICE];				// input = The memory of input data.
vector<int> map[MAX];	// map = The memory of map data (Yut).
bool visit[MAX][MAX];		// visit = The memory of visited or not.
vector<Knight>vc;			// vc = The memory of knight's location and score.
int answer = 0;				// answer = The maximum value as output.

int Sum()		// To figure out the total score.
{
	int tot = 0;
	for (int i = 0; i < 5; i++)
		tot += vc[i].score;
	return tot;
}

void Init()		// To initialize the knight data and draw a Yut's map.
{
	for (int i = 0; i < 5; i++)
		vc.push_back({ 0,0,0 });		// Initialize the knights.

										// map[0] : Start.	map[-1] : End.	
	for (int i = 0; i <= 20; i++)		// Outer line.
		map[i].push_back(2 * i);
	for (int j = 1; j <= 3; j++)		// Shortcut in [y=5 / y=15].
	{
		map[5].push_back(10 + 3 * j);
		map[15].push_back(29 - j);
	}
	for (int j = 1; j <= 2; j++)		// Shortcut in [y=10].
		map[10].push_back(20 + j * 2);
	map[10].push_back(25);
	for (int j = 1; j <= 2; j++)
		map[10].push_back(25 + j * 5);
}

bool Moved(int idx, int cnt)
{
	int y = vc[idx].y, x = vc[idx].x, s = vc[idx].score;
	visit[y][x] = false;	// For moving.
	int num = input[cnt];
	if (y == 5)		// First fork.
	{
		if (x + num < 4)	// [5][x].
			x += num;
		else		// Go by [10][3].
		{
			y = 10;
			int dist = 4 - x;
			num -= dist;
			x = 3;		// From [10][3].

			if (x + num >= 6)		// End.
			{
				if (x + num == 6)		// Last position.
				{
					y = 20;
					x = 0;
				}
				else
					x = 25;		// Treat as destination.
			}
			else
				x += num;
		}
	}

	else if (y == 10)		// Second fork.
	{							// [10][x]
		if (x + num >= 6)			// End.
		{
			if (x + num == 6)		// Last position.
			{
				y = 20;
				x = 0;
			}
			else
				x = 25;		// Treat as destination.
		}
		else
			x += num;
	}

	else if (y == 15)		// Third fork.
	{
		if (x + num < 4)	// [15][x].
			x += num;
		else		// Go by [10][3].
		{
			y = 10;
			int dist = 4 - x;
			num -= dist;
			x = 3;		// From [10][3].

			if (x + num >= 6)			// End.
			{
				if (x + num == 6)		// Last position.
				{
					y = 20;
					x = 0;
				}
				else
					x = 25;		// Treat as destination.
			}
			else
				x += num;
		}
	}

	else		// Outer line.
	{
		if (y + num <= 20)	// Move on Outline.
			y += num;
		else						// End.
			y = 25;		// Treat as destination.
	}

	if (y == 25 || x == 25)		// End.
	{
		vc[idx] = { 25,25,s };
		return true;
	}

	if (visit[y][x])		// Already visited.
		return false;

	vc[idx] = { y,x,s + map[y][x] };	// Update.
	visit[y][x] = true;
	return true;
}

void DFS(int cnt)			// To do exhaustive search.
{
	if (cnt == 10)			// Base case. [The whole of dice input.]
	{	
		answer = max(answer, Sum());		// Compare the biggiest sum.
		return;
	}

	for (int i = 1; i < 5; i++)
	{
		if (vc[i].y == 25 && vc[i].x == 25)		// Arrived at destination.
			continue;

		int py = vc[i].y, px = vc[i].x, ps = vc[i].score;		// Previous data.
		if (!Moved(i, cnt))		// Moved the current knight with dice value.
		{
			visit[py][px] = true;
			continue;
		}
		DFS(cnt + 1);
		visit[vc[i].y][vc[i].x] = false;	// Return to previous one.
		vc[i] = { py,px,ps };	
		visit[py][px] = true;
	}
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);	cout.tie(0);

	for (int i = 0; i < 10; i++)
		cin >> input[i];				// Input data.

	Init();									// Draw the Yut map.
	DFS(0);								// Exhaustive search.
	cout << answer << endl;		// Output.
}