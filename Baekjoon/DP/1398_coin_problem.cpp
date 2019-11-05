#include<iostream>
#include<algorithm>
#include<memory.h>

#define MAX 101

using namespace std;

int coin[3] = { 1,10,25 };			// coin = The memory of coin's base state.
int cache[MAX];						// cache = The memory of memoization.

int Change(long long price)		// To make changes..
{
	int cnt = 0;
	while (price != 0)
	{
		cnt += cache[price % 100];		// [78�� 7800, 780000�� ��� ������ ������ �������� ȯ���ȴ�.]
		price /= 100;							// [�̷��� Ư���� ������� cache�� 100������ ���ؼ� �̿�.]
	}
	return cnt;
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);	cout.tie(0);

	memset(cache, 127, sizeof(cache));			// Initialization as Infinite value.
	cache[0] = 0;											// Base state.
	for (int i = 1; i < MAX; i++)
	{
		for (int j = 0; j < 3; j++)	// Coin has similar pattern with base state.[1, 10, 25]	
		{
			if (i - coin[j] >= 0)		
				cache[i] = min(cache[i], cache[i - coin[j]] + 1);		// Formula.
		}
	}

	int test_case;
	cin >> test_case;
	for (int t = 1; t <= test_case; t++)
	{
		long long price;							// price = The target price.
		cin >> price;								// Input.
		cout << Change(price) << endl;	// Output.
	}
}