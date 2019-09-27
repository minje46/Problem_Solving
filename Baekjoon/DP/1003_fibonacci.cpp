#include<iostream>
#include<memory.h>

#define MAX 41
using namespace std;

int cache[MAX][2];		// cache = The memory of cache for memoization.

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);			cout.tie(0);

	memset(cache, 0, sizeof(cache));			// Initialization.
	cache[0][0] = 1;	cache[0][1] = 0;	// Fibonacci[0].	
	cache[1][0] = 0;	cache[1][1] = 1;	// Fibonacci[1];
	for (int i = 2; i < MAX; i++)
	{
		for (int j = 0; j < 2; j++)
			cache[i][j] = cache[i - 1][j] + cache[i - 2][j];		// Formula of fibonacci.
	}

	int test_case;
	cin >> test_case;
	for (int t = 1; t <= test_case; t++)		// Test case.
	{
		int fibo;
		cin >> fibo;
		cout << cache[fibo][0] << " " << cache[fibo][1] << endl;		// Output.
	}
}