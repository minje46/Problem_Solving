#include<iostream>
#include<algorithm>
#include<memory.h>
#include<vector>

#define MAX 11
#define INF 987654321

using namespace std;

int paper[6] = { 0,5,5,5,5,5 };		// paper = The fixed number of coloerd papers from (1x1) ~ (5x5).
int map[MAX][MAX];					// map = The memory of original map data.
int answer = INF, cnt = 0;				// answer = The minimum number of used colored papers.		cnt = The counted papers.

bool Check(int y, int x, int n)		// To check whethere square space is enough or not.
{
	for (int i = y; i < y + n; i++)	// From current location.
	{
		for (int j = x; j < x + n; j++)	// To attached n size's colored papers.
		{
			if (map[i][j] != 1)		// If there is wall, it is impossible to do.
				return false;
		}
	}
	return true;
}

void Visit(int y, int x, int n, int val)		// To attach or deattach the n size colored papers.
{
	for (int i = y; i < y + n; i++)
	{
		for (int j = x; j < x + n; j++)
			map[i][j] = val;		// [주어진 val을 이용하여, attach와 deattach를 수행.]
	}
}

void DFS(int y, int x)		// To do exhaustive search from (1,1) to (10,10).
{
	if (x == MAX)		// Initialize the position as 1.
	{
		DFS(y + 1, 1);
		return;
	}

	if (y == MAX)		// Arrived at destination.
	{						// [Base case.]
		answer = min(answer, cnt);		// Compare the used papers.
		return;
	}

	if (map[y][x] == 0)		// If here is wall, it doesn't need to search more.
	{
		DFS(y, x + 1);			// Go to next coordinates.
		return;
	}

	for (int n = 5; n > 0; n--)		// The size of colored papers.
	{
		if (paper[n] == 0 || y + n > MAX || x + n > MAX)		// Paper starvation. + Overflow.
			continue;

		if (!Check(y, x, n))		// To check it is enough to use n size colored paper.
			continue;

		Visit(y, x, n, 0);		// Changed to n size papers.
		paper[n]--;			// Decrease used size paper.
		cnt++;					// Increase the total number of used papers.

		DFS(y, x + n);			// Keep searching.

		Visit(y, x, n, 1);		// Return to previous one.
		paper[n]++;
		cnt--;
	}
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	for (int i = 1; i < MAX; i++)
	{
		for (int j = 1; j < MAX; j++)
			cin >> map[i][j];			// Original map data.
	}

	DFS(1, 1);

	if (answer == INF)			// Impossible case.
		cout << -1 << endl;
	else								// Possible case.
		cout << answer << endl;
}

