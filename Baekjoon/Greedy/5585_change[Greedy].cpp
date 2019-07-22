#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

int coin[6] = { 500, 100, 50, 10, 5, 1 };		// coin = The memory of base coins we have.

int Change(int extra)		// To make a change with extra money.
{
	int cnt = 0;
	while (extra)
	{
		for (int i = 0; i < 6; i++)	// In whole of coins.
		{
			if (coin[i] <= extra)		// The biggest coin is picked.
			{
				extra -= coin[i];
				break;
			}
		}
		cnt++;
	}

	return cnt;
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int N;			// N = The cost of paying.
	cin >> N;

	cout << Change(1000 - N) << endl;
}