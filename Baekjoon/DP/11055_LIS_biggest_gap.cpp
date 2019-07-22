#include<iostream>
#include<algorithm>

using namespace std;

int N, max_tot = 0;					// N = the number of elements.			max_tot = The biggest sum of subsequence.
int *arr, *memo;						// arr = Allocate the memory of input.		memo = Allocate memory of memoization.

void Biggest_gap()					// Do memoization and find the biggest sum.
{
	for (int i = 0; i < N; i++)		// [i가 비교를 위한 기준 값이고,
	{
		for (int j = 0; j < i; j++)		// [j가 0부터 i까지 순서대로 비교를 위한 값이다.]
		{
			if (arr[i] > arr[j])			// If the number is larger than previous. [새로운 기준 값이 증가하는 수열일 경우.]
				memo[i] = max(memo[i], memo[j] + arr[i]);		// Update the memo.	[현재 값과 이전까지의 sum 값+ 현재 값 중에서 max 값 선택]
		}
		max_tot = max(memo[i], max_tot);								// Get the max sum.	[최대값 저장.]
	}
}

int main(void)
{
	cin >> N;							// Input of elements.

	arr = new int[N];					// Allocate memory.
	memo = new int[N];			// Allocate memory.
	for (int i = 0; i < N; i++)
	{
		cin >> arr[i];					// Input of arrays.
		memo[i] = arr[i];			// Initailize the memo.
	}
	
	Biggest_gap();					// Do memoization and find the biggest sum.

	cout << max_tot << endl;		// Output of lis.
}