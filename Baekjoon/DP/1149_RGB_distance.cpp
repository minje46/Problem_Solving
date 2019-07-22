#include<iostream>
#include<algorithm>

#define MAX 1001

using namespace std;

int memo[MAX][3];		// memo = The memory of memoization to store each cost with R[0], G[1], B[2].

int main(void)
{
	ios_base::sync_with_stdio(false);

	int N;						// N = The size of map as input.
	cin >> N;
	for (int i = 1; i <= N; i++)
	{
		cin >> memo[i][0] >> memo[i][1] >> memo[i][2];

		memo[i][0] += min(memo[i - 1][1], memo[i - 1][2]);			// [이전에 Red를 선택했을 경우, Green 과 Blue 중에서 minimum cost를 선택.]
		memo[i][1] += min(memo[i - 1][0], memo[i - 1][2]);			// [이전에 Green를 선택했을 경우, Red와 Blue 중에서 minimum cost를 선택.]
		memo[i][2] += min(memo[i - 1][0], memo[i - 1][1]);			// [이전에 Blue를 선택했을 경우, Red와 Green 중에서 minimum cost를 선택.]
	}

	cout << min(memo[N][0], min(memo[N][1], memo[N][2])) << endl;			// The minimum cost in RGB.
}