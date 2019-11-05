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
			cache[j] += cache[j - coin[i]];	// [cache[j-coin[i]] > 0 �̶�� ����, cache[j-coin[i]]�� ���� �� �ִ� ����� �����ϰ�,
	}														// coin[j]�� ���ؼ� cache[j]�� ���� �� �ִٴ� ���� �ǹ��Ѵ�.]
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