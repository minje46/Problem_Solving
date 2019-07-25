#include<iostream>
#include<algorithm>
#include<vector>

#define MAX 1000001

using namespace std;

int cache[MAX] = { 0, };		// cache = The memory of memoization.

void Organize(int n)		// To organize the minimum counts of division based on memoization.
{
	cache[1] = 0;			// Base case.

	for (int i = 2; i <= n; i++)
	{
		cache[i] = cache[i - 1] + 1;		// It is possible for every case.
	// To distinguish the value is able to be divided by two or three.
		if (i % 2 == 0)
			cache[i] = min(cache[i], cache[i / 2] + 1);
		if (i % 3 == 0)
			cache[i] = min(cache[i], cache[i / 3] + 1);
	}
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int N;					// N = The value to divide as small as we do.
	cin >> N;

	Organize(N);		// To organize the minimum counts of division.

	cout << cache[N] << endl;		// The value N's minimum division.
}