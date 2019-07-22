#include<iostream>
#include<algorithm>

using namespace std;

int N, max_tot = 0;					// N = the number of elements.			max_tot = The biggest sum of subsequence.
int *arr, *memo;						// arr = Allocate the memory of input.		memo = Allocate memory of memoization.

void Biggest_gap()					// Do memoization and find the biggest sum.
{
	for (int i = 0; i < N; i++)		// [i�� �񱳸� ���� ���� ���̰�,
	{
		for (int j = 0; j < i; j++)		// [j�� 0���� i���� ������� �񱳸� ���� ���̴�.]
		{
			if (arr[i] > arr[j])			// If the number is larger than previous. [���ο� ���� ���� �����ϴ� ������ ���.]
				memo[i] = max(memo[i], memo[j] + arr[i]);		// Update the memo.	[���� ���� ���������� sum ��+ ���� �� �߿��� max �� ����]
		}
		max_tot = max(memo[i], max_tot);								// Get the max sum.	[�ִ밪 ����.]
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