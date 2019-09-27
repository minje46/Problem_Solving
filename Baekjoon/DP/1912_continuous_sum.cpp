#include<iostream>
#include<algorithm>
#include<memory.h>

#define MAX 100001
using namespace std;

long long cache[MAX];		// cache = The memory of cache for memoization.

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);			cout.tie(0);

	long long N, answer;		// N = The number of inputs.			answer = The maximum continuous sum as output.
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		cin >> cache[i];			// Input.

		if (i == 0)					// Execption.
		{
			answer = cache[i];	// Initialization.
			continue;
		}
		cache[i] = max(cache[i], cache[i - 1] + cache[i]);		// Formula. [The current input & continuous sum.]
		answer = max(answer, cache[i]);		// Compare the maximum sum.
	}
	cout << answer << endl;		// Output.
}