#include<iostream>
#include<algorithm>
#include<memory.h>
#include<cmath>
//#pragma warning(disable:4996)

#define MAX 21

using namespace std;

int N, M;		// N = The size of map.		M = The cost to pay from each home.
int map[MAX][MAX];		// map = The memory of original map data.

bool Range(int y, int x)		// To check whether (y,x) is possible area or not.
{
	if ((y >= 0 && y < N) && (x >= 0 && x < N))		// Possible range.
		return true;
	else
		return false;
}

int Count(int y, int x, int k)		// To count the number of house.
{
	int cnt = 0, nx, endp;		
	for (int i = 1; i < k; i++)
	{
		int up = y - k + i;
		int down = y + k - i;

		endp = i * 2 - 1;
		nx = x - endp / 2;

		for (int j = 0; j < endp; j++)
		{
			if (Range(up, nx + j) && (map[up][nx + j]))
				cnt++;
			if (Range(down, nx + j) && (map[down][nx + j]))
				cnt++;
		}
	}

	endp = k * 2 - 1;
	nx = x - endp / 2;
	for (int i = 0; i < endp; i++)
	{
		if (Range(y, nx + i) && map[y][nx + i])
			cnt++;
	}
	return cnt;
}


int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	//freopen("input.txt", "r", stdin);

	int test_case;
	cin >> test_case;
	for (int t = 1; t <= test_case; t++)
	{	// Initialization.
		memset(map, 0, sizeof(map));

		cin >> N >> M;
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
				cin >> map[i][j];
		}

		int answer = 0;		// answer = The maximum number of homes to be included in security area.
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				for (int k = 1; k <= MAX; k++)
				{
					int cnt = Count(i, j, k);
					int service = pow(k, 2) + pow(k - 1, 2);
					int cost = cnt * M;

					if (cost >= service)
						answer = max(answer, cnt);
				}
			}
		}
		cout << "#" << t << " " << answer << endl;
	}
}