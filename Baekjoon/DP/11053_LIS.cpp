#include<iostream>
#include<algorithm>

using namespace std;

int N, ans;								// N = the number of elements.			ans = The longest length of subsequence.
int *arr, *memo;						// arr = Allocate the memory of input.		memo = Allocate memory of memoization.

void LIS()								// Do memoization and find the max length.
{
	for (int i = 0; i < N; i++)
	{
		memo[i] = 1;					// Initialize the memo.
		for (int j = 0; j < i; j++)
			if (arr[i] > arr[j])			// If the number is larger than previous.
				memo[i] = max(memo[i], memo[j] + 1);		// Update the memo.
		ans = max(ans, memo[i]);									// Get the max length.
	}
}

int main(void)			
{
	cin >> N;								// Input of elements.
	arr = new int[N];						// Allocate memory.
	memo = new int[N];				// Allocate memory.

	for (int i = 0; i < N; i++)
		cin >> arr[i];						// Input of arrays.
	
	LIS();										// Do memoization and find the longest length.
	
	cout << ans << endl;				// Output of lis.
}