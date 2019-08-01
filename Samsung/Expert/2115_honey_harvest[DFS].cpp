#include<iostream>
#include<algorithm>
#include<memory.h>
//#pragma warning(disable:4996)

#define MAX 11

using namespace std;

int N, M, C;		// N = The size of map.		M = The number of honey bottles.			C = The maximum capacity of total honey.
int map[MAX][MAX];		// map = The memory of original data.
bool visit[MAX][MAX];		// visit = The memory of visited or not.
int result = 0;

void getPrice(int y, int x, int cnt, int total, int profit)		// To figure out the maximum profits with sections. [Do backtracking.]
{							// [Base case���� �����ϴ� dfs + Backtracking�� ���� dfs.]
	if (total > C)		// Base case #1.
		return;			// The total honey should be smaller than capacity.

	result = max(result, profit);		// Compare the profits.

	if (cnt == M)		// Base case #2.
		return;			//  The number of sections to harvest was fixed as M.

	getPrice(y, x + 1, cnt + 1, total + map[y][x], profit + pow(map[y][x], 2));		// [1���� ������Ű�鼭, dfs ����.]
	getPrice(y, x + 1, cnt + 1, total, profit);		// [Base case ������ ���, Backtracking�� ���� ������ ����(���� dfs�� ����.) �� �ܰ迡�� dfs�� ����.]
}

int Harvest(int y, int x)
{
	for (int i = 0; i < M; i++)
		visit[y][x + i] = true;

	result = 0;
	getPrice(y, x, 0, 0, 0);		// To calculate the max profits with visited section.
	int First = result;				// The first case of honey harvest.

	int Second = 0;				// Then second case of honey harvest.
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N - M + 1; j++)
		{
			if (!visit[i][j])			// Except visited sections. 
			{							// [visit = true ��� ����, first case �Ǵ� ���� dfs���� Ž���� max ���� result�� ����Ǿ� �ֱ� ������, pass ����.]
				result = 0;
				getPrice(i, j, 0, 0, 0);
				Second = max(Second, result);
			}
		}
	}

	return First + Second;		// The total profits.
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
		memset(visit, false, sizeof(visit));

		cin >> N >> M >> C;			// Input data.
		for (int i = 1; i <= N; i++)
		{
			for (int j = 1; j <= N; j++)
				cin >> map[i][j];
		}

		int answer = 0;			// The total price of both honey's profits.
		for (int i = 1; i <= N; i++)
		{
			for (int j = 1; j <= N - M + 1; j++)
				answer = max(answer, Harvest(i, j));		// To figure out the total honey's profits based on (i,j) area.
		}
		cout << "#" << t << " " << answer << endl;
	}
}