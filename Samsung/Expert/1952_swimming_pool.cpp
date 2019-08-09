#include<iostream>
#include<algorithm>
#include<memory.h>
//#pragma warning(disable:4996)

#define MAX 13
#define TYPE 5
#define INF 987654321

using namespace std;

int month[MAX];			// month = The memory of each month usage.
int cost[TYPE];			// cost = The memory of each ticket's price.
int answer = INF;			// answer = The minimum total cost of usage.

void DFS(int idx, int sum)		// To search the whole of cases based on dfs algorithm.
{
	if (idx >= 13)		// Base case.
	{
		answer = min(answer, sum);		// Compare the minimum value.
		return;
	}

	if (month[idx] > 0)		// To decrease the time wasting.
	{
		DFS(idx + 1, sum + month[idx] * cost[1]);		// 1day pass.
		DFS(idx + 1, sum + cost[2]);		// 1month pass.
		DFS(idx + 3, sum + cost[3]);		// 3months package.
	}
	else
		DFS(idx + 1, sum);		// If the value is zero, it doesn't need to calculate.
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
		memset(month, 0, sizeof(month));
		memset(cost, 0, sizeof(cost));
		answer = INF;

		for (int i = 1; i < TYPE; i++)
			cin >> cost[i];				// Ticket price.

		for (int i = 1; i < MAX; i++)
			cin >> month[i];				// Month usage.
			
		DFS(1, 0);		// [Index , Sum]

		answer = min(answer, cost[4]);	// Compare the year pass.

		cout << "#" << t << " " << answer << endl;		// The minimum price of year's ticket cost.
	}
}