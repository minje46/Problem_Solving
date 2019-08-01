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
								// [M의 구역 내에서 Max profit을 낼 수 있는 값을 search.]
	return max(Max_Price(vc, cnt + 1, total + vc[cnt], profit + pow(vc[cnt], 2)), Max_Price(vc, cnt + 1, total, profit));
}

int Memoization(int y, int x)		// To do memoization based on max profits.
{
	vector<int> vc;		// vc = The memory for harvest section.
	for (int i = 0; i < M; i++)
		vc.push_back(map[y][x + i]);		// [M의 영역만큼 vector에 값을 저장.]

	return Max_Price(vc, 0, 0, 0);			// [선택된 영역 내에서 Max profit값을 return 해준다.]
}

int DFS(int y, int x)
{
	int answer = 0;

	for (int i = x + M; i <= N - M + 1; i++)		// [Main에서 Cache[i][j] 이외를 dfs 하는 것이므로, (i,j)의 영역을 제외한 영역부터 서칭.]
		answer = max(answer, cache[y][i]);		// [해당 row에서 (i,j)를 제외한 나머지 M 영역 중 max 값 선택.]

	for (int i = y + 1; i <= N; i++)					// [Row를 증가시키면서, 모든 column M 영역 search.]
	{
		for (int j = 1; j <= N; j++)					// [이후, Max 영역 한개 선택.]
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
			for (int j = 1; j <= N - M + 1; j++)		// [각 M의 영역만큼, 차례대로 MAX value를 찾는다.]
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