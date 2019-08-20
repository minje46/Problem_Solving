#include<iostream>
#include<memory.h>
//#pragma warning(disable:4996)

#define MAX 21

using namespace std;

int N, X;					// N = The size of map.				X = The length of slope.
int map[MAX][MAX];			// map = The memory of original input data.
int answer = 0;		// answer = The number of runways as output.

bool Horizon(int row)		// To figure out whether the runway is possible or not in each row.
{
	int cnt = 1;
	int cur = map[row][0];
	for (int j = 1; j < N; j++)		// Row.
	{
		if (cur == map[row][j])		// Same height.
			cnt++;

		else if (cur + 1 == map[row][j])		// Higher.
		{
			if (cnt >= X)
			{
				cnt = 1;		// Initialize the count.
				cur = map[row][j];		// Change the new height.
			}
			else		// Can't build slope.
				return false;
		}

		else if (cur - 1 == map[row][j])		// Lower.
		{
			cur = map[row][j];
			for (int k = j; k < j + X; k++)		
			{
				if (cur != map[row][k])	// Check whether it is possible to build slope or not.
					return false;				// based on minimum X'th height. 
			}
			j += X - 1;
			cnt = 0;
		}

		else
			return false;
	}
	return true;
}

bool Vertical(int col)		// To figure out whether the runway is possible or not in each column.
{
	int cnt = 1;
	int cur = map[0][col];
	for (int j = 1; j < N; j++)		// Row.
	{
		if (cur == map[j][col])		// Same height.
			cnt++;

		else if (cur + 1 == map[j][col])		// Higher.
		{
			if (cnt >= X)
			{
				cnt = 1;		// Initialize the count.
				cur = map[j][col];		// Change the new height.
			}
			else		// Can't build slope.
				return false;
		}

		else if (cur - 1 == map[j][col])		// Lower.
		{
			cur = map[j][col];
			for (int k = j; k < j + X; k++)
			{
				if (cur != map[k][col])		// Check whether it is possible to build slope or not.
					return false;				// based on minimum X'th height. 
			}
			j += X - 1;
			cnt = 0;
		}

		else
			return false;
	}
	return true;
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);

//	freopen("input.txt", "r", stdin);

	int test_case;
	cin >> test_case;
	for (int t = 1; t <= test_case; t++)
	{	// Initialization.
		memset(map, 0, sizeof(map));
		answer = 0;

		cin >> N >> X;
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
				cin >> map[i][j];
		}

		for (int i = 0; i < N; i++)
		{
			if (Horizon(i))		// Check each row.
				answer++;

			if (Vertical(i))		// Check each column.
				answer++;
		}

		cout << "#" << t << " " << answer << endl;
	}
}