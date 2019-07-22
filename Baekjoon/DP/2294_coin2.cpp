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
	{										// [�� coin���� ���� �� �ִ� ���� ��ü�� ��.]
		for (int j = 0; j <= tot; j++)		// From zero to total money which is the target.
		{									// [0�� ���� ��ǥ �ݾ� tot ����.]
			if (j >= coin[i] && memo[j - coin[i]] != -1)		// [j�� ��ǥ �ݾ����μ�, ������ ������� �� �ִ� coin[i]���ٴ� �翬�� Ŀ�� �ϰ�,
			{		// ��ǥ �ݾ��� j�� ���� ���� coin[i]�� �� �ݾ��� ��, ������ ������ �������� ��� ���ο� ���� coin[i]���� �񱳰� ����.]
				if (memo[j] == -1)		// [��ǥ �ݾ� j�� ���� �� �ִ� ������ ���� ���, ����(memo[j-coin[i]) ������ �� +1�� ���Ӱ� ���� ����.]	
					memo[j] = memo[j - coin[i]] + 1;
				else						// [��ǥ �ݾ� j�� ���� �� �ִ� ������ �̹� �����ϴ� ����, �ּҸ� �̷�� ������ ����.]
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