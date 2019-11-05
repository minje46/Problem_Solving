#include<iostream>
#include<memory.h>

#define COIN 101
#define MAX 10001

using namespace std;

int N, K;					// N = The number of coin types.			K = The target money to make.
int coin[COIN];		// coin = The memory of coin value.
int cache[MAX];		// cache = The memory of number of cases as memoization.

void DP()		// To do dynamic programming.
{
	memset(cache, 0, sizeof(cache));
	cache[0] = 1;			// Base state.
	for (int i = 0; i < N; i++)
	{
		for (int j = coin[i]; j <= K; j++)			// Formula.
			cache[j] += cache[j - coin[i]];	// [cache[j-coin[i]] > 0 이라는 것은, cache[j-coin[i]]을 만들 수 있는 방법이 존재하고,
	}														// coin[j]를 더해서 cache[j]를 만들어낼 수 있다는 것을 의미한다.]
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);	cout.tie(0);

	cin >> N >> K;
	for (int i = 0; i < N; i++)
		cin >> coin[i];					// Input data.
	DP();										// Memoization.	
	cout << cache[K] << endl;		// Output.
}