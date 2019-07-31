#include<iostream>
#include<algorithm>
#include<memory.h>

#define MAX 301

using namespace std;

int stair[MAX];				// stair = The memory of stair value.
int cache[MAX];				// cache = The memory of memoization.

void Climb(int n)			// To figure out the maximum value could climb.
{	// Initialization on cache memory before memoization.
	cache[1] = stair[1];		// Base case.
	cache[2] = max(stair[1] + stair[2], stair[2]);		// The bigger one between (stair[1]+[2]) and (stair[2]).
	cache[3] = max(stair[1] + stair[3], stair[2] + stair[3]);		// The bigger one between (stair[1]+[3]) and (stair[2]+[3]).
																	// Dynamic programming.
	for (int i = 4; i <= n; i++)		// Recurrence formula.
		cache[i] += max(cache[i - 3] + stair[i - 1] + stair[i], cache[i - 2] + stair[i]);		// Choose the bigger one.
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int N;				// N = The number of total stairs.
	cin >> N;
	for (int i = 1; i <= N; i++)
		cin >> stair[i];

	Climb(N);		// To figure out the maximum value can climb these stairs.

	cout << cache[N] << endl;		// The maximum value at the last stair as output.
}