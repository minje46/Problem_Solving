#include<iostream>
#include<algorithm>
#include<memory.h>
//#pragma warning(disable:4996)

#define MAX 13
#define INF 987654321

using namespace std;

int N;			// N = The number of candidate numbers.
int numbers[MAX];		// numbers = The memory of cadidate numbers.
int calculate[4];			// calculate = The memory of four fundamental arithmetic operations.
int small, big;				// small = The memory of smallest value.			big = The memory of biggest value.

void DFS(int n_idx, int c_idx, int tot)		// To do exhaustive search in all cases.
{
	if (n_idx == N)		// Base case. [Use the whole of number cards.]
	{
		small = min(small, tot);		// Compare smaller one.
		big = max(big, tot);				// Compare bigger one.
		return;
	}

	for (int i = 0; i < 4; i++)	// In four fundamental arithmetic operations.
	{									// [0 : '+'] [1 : '-'] [2 : '*'] [3 : '/']
		if (calculate[i] == 0)
			continue;

		calculate[i] -= 1;		// Used this operator.
		switch (i)
		{
		case 0:		// [0:'+']
			DFS(n_idx + 1, i, tot + numbers[n_idx]);
			break;
		case 1:		// [1 : '-']
			DFS(n_idx + 1, i, tot - numbers[n_idx]);
			break;
		case 2:		// [2 : '*']
			DFS(n_idx + 1, i, tot * numbers[n_idx]);
			break;
		case 3:		// [3 : '/']
			DFS(n_idx + 1, i, tot / numbers[n_idx]);
			break;
		default:
			break;
		}
		calculate[i] += 1;	// Return to previous one.
	}
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
		memset(numbers, 0, sizeof(numbers));
		memset(calculate, 0, sizeof(calculate));
		small = INF, big = -INF;

		cin >> N;
		for (int i = 0; i < 4; i++)	// [0 : '+'] [1 : '-'] [2 : '*'] [3 : '/']
			cin >> calculate[i];
		for (int i = 0; i < N; i++)
			cin >> numbers[i];		// Input data.

		DFS(1, 0, numbers[0]);	// Simulation.

		cout << "#" << t << " " << big - small << endl;		// Output.
	}
}