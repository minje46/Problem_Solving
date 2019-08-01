#include<iostream>
#include<algorithm>
#include<memory.h>
#include<vector>
//#pragma warning(disable:4996)

#define MAX 11

using namespace std;

int N, M, C;		// N = The size of map.		M = The number of honey bottles.			C = The maximum capacity of total honey.
int map[MAX][MAX];		// map = The memory of original data.
int cache[MAX][MAX];	// cache = The memory of memoization.

int Max_Price(vector<int> &vc, int cnt, int total, int profit)			// To figure out the maximum profits.
{
	if (total > C)			// Base case #1.
		return 0;				// The total honey should be smaller than capacity.

	if (cnt == M)			// Base case #2.
		return profit;		//  The number of sections to harvest was fixed as M.
								// [M�� ���� ������ Max profit�� �� �� �ִ� ���� search.]
	return max(Max_Price(vc, cnt + 1, total + vc[cnt], profit + pow(vc[cnt], 2)), Max_Price(vc, cnt + 1, total, profit));
}

int Memoization(int y, int x)		// To do memoization based on max profits.
{
	vector<int> vc;		// vc = The memory for harvest section.
	for (int i = 0; i < M; i++)
		vc.push_back(map[y][x + i]);		// [M�� ������ŭ vector�� ���� ����.]

	return Max_Price(vc, 0, 0, 0);			// [���õ� ���� ������ Max profit���� return ���ش�.]
}

int DFS(int y, int x)
{
	int answer = 0;

	for (int i = x + M; i <= N - M + 1; i++)		// [Main���� Cache[i][j] �ܸ̿� dfs �ϴ� ���̹Ƿ�, (i,j)�� ������ ������ �������� ��Ī.]
		answer = max(answer, cache[y][i]);		// [�ش� row���� (i,j)�� ������ ������ M ���� �� max �� ����.]

	for (int i = y + 1; i <= N; i++)					// [Row�� ������Ű�鼭, ��� column M ���� search.]
	{
		for (int j = 1; j <= N; j++)					// [����, Max ���� �Ѱ� ����.]
			answer = max(answer, cache[i][j]);
	}

	return answer;
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
		memset(cache, 0, sizeof(cache));

		cin >> N >> M >> C;			// Input data.
		for (int i = 1; i <= N; i++)
		{
			for (int j = 1; j <= N; j++)
				cin >> map[i][j];
		}

		for (int i = 1; i <= N; i++)		// Memoization.
		{
			for (int j = 1; j <= N - M + 1; j++)		// [�� M�� ������ŭ, ���ʴ�� MAX value�� ã�´�.]
			{
				cache[i][j] = Memoization(i, j);			
			}
		}

		int answer = 0;			// The total price of both honey's profits.
		for (int i = 1; i <= N; i++)
		{
			for (int j = 1; j <= N - M + 1; j++)
				answer = max(answer, DFS(i, j) + cache[i][j]); 	// To figure out the total honey's profits based on (i,j) area.
		}
		cout << "#" << t << " " << answer << endl;
	}
}