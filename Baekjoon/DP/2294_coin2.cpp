#include<iostream>
#include<algorithm>
#include<memory.h>

using namespace std;

int coin[101];							// coin = The memory of coin's cost.
int memo[10001] = { 0, };		// memo = The memory for memoization.

void Convert(int n, int tot)			// Do compare the whole of cases which are set of combinations based on all coins.	
{
	memset(memo, -1, sizeof(memo));			// Do initialize the memo memory to distinguish impossible combinations.
	memo[0] = 0;					// The first case. [Exception.]

	for (int i = 0; i < n; i++)			// Compare all coins in a row.
	{										// [각 coin으로 만들 수 있는 조합 전체를 비교.]
		for (int j = 0; j <= tot; j++)		// From zero to total money which is the target.
		{									// [0원 부터 목표 금액 tot 까지.]
			if (j >= coin[i] && memo[j - coin[i]] != -1)		// [j가 목표 금액으로서, 조합이 만들어질 수 있는 coin[i]보다는 당연히 커야 하고,
			{		// 목표 금액인 j와 현재 동전 coin[i]를 뺀 금액일 때, 가능한 조합이 존재했을 경우 새로운 동전 coin[i]으로 비교가 가능.]
				if (memo[j] == -1)		// [목표 금액 j를 맞출 수 있는 조합이 없는 경우, 이전(memo[j-coin[i]) 조합의 수 +1로 새롭게 조합 가능.]	
					memo[j] = memo[j - coin[i]] + 1;
				else						// [목표 금액 j를 맞출 수 있는 조합이 이미 존재하는 경우는, 최소를 이루는 조합을 선택.]
					memo[j] = min(memo[j], memo[j - coin[i]] + 1);			
			}
		}
	}
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int N, K;				// N = The number of coins.			K = The total money.
	cin >> N >> K;
	for (int i = 0; i < N; i++)
		cin >> coin[i];

	Convert(N, K);	// Do compare the whole of cases which are set of combinations based on all coins.	

	cout << memo[K] << endl;		// The minimum number of coin's combination.
}