#include<iostream>
#include<algorithm>

#define MAX 91

using namespace std;

long long memo[MAX];			// The memory of memoization.
long long zero_cnt[MAX];			// The count memory of zero.
long long one_cnt[MAX];			// The count memory of one.	

int main(void)
{
	ios_base::sync_with_stdio(false);

	int N;				// N = The size of positional number.
	cin >> N;

	memo[1] = 1;		// The base case.
	zero_cnt[1] = 0;		// The base case.
	one_cnt[1] = 1;		// The base case.
	for (int i = 2; i <= N; i++)
	{							// [N-1의 0의 개수 *2 는 0일 경우, 0과 1 모두 N번째 자리에 올 수 있기 때문이다.]
		memo[i] = zero_cnt[i - 1] * 2 + one_cnt[i - 1];		// [N-1의 마지막 숫자가 1일 경우, 무조건 0만 올 수 있기 때문에 N-1의 0의 개수와 동일.]	
		one_cnt[i] = zero_cnt[i - 1];		// [N번째의 마지막 자리가 1인 경우는, N-1번째의 0의 개수 만큼 1이 나올 수 있다.]
		zero_cnt[i] = one_cnt[i - 1] + zero_cnt[i-1];		// [N번째의 마지막 자리가 0인 경우는, N-1번째의 1의 개수와 0의 개수 만큼 0이 나올 수 있다.]
	}

	cout << memo[N] << endl;		// Output.
}