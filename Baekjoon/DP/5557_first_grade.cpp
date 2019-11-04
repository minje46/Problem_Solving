#include<iostream>
#include<memory.h>

#define MAX 101

using namespace std;

int	N;										// N = The number of input.		
int input[MAX];						// input = The memory of input data.
long long cache[22][MAX];		// cache = The memory of memoization.

long long DP(int idx, int val)		// To do dynamic programming.
{
	if (val < 0 || val>20)	// Base case.
		return 0;

	if (idx == N - 2)			// Base case.
	{								// Correct formula or not.	
		if (val == input[N - 1])		
			return 1;
		else
			return 0;
	}

	long long &result = cache[val][idx];
	if (result != -1)			// Load the value.
		return result;

	result = 0;					// Empty. [Addition] [Subtraction]	
	return result += (DP(idx + 1, val + input[idx + 1]) + DP(idx + 1, val - input[idx + 1]));
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);	cout.tie(0);

	cin >> N;
	for (int i = 0; i < N; i++)
		cin >> input[i];								// Input data.

	memset(cache, -1, sizeof(cache));		// Initialization.
	cout << DP(0, input[0]) << endl;			// Output.
}