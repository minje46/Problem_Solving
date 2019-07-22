#include<iostream>
#include<algorithm>

#define MAX 1001

using namespace std;

int memo[MAX];			// The memory of memoization.

void Tiling(int N)			// To figure out the recurrence relation(��ȭ��) of the number of tile's.
{								// [Ÿ���� ������ count�ϴ� ��ȭ��.]	
	memo[1] = 1;		// The base case.	[n-1].
	memo[2] = 2;		// The base case.	[n-2].
	for (int i = 3; i <= N; i++)
		memo[i] = (memo[i - 2] + memo[i - 1]) % 10007;			// The recurrence relation. [Same as Fibonacci.]
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	
	int N;						// The size of square.	[Square�� ũ��.]
	cin >> N;
	
	Tiling(N);				// To figure out the recurrence relation(��ȭ��) of the number of tile's.

	cout << memo[N] << endl;		// Output.
}