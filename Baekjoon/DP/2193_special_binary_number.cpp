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
	{							// [N-1�� 0�� ���� *2 �� 0�� ���, 0�� 1 ��� N��° �ڸ��� �� �� �ֱ� �����̴�.]
		memo[i] = zero_cnt[i - 1] * 2 + one_cnt[i - 1];		// [N-1�� ������ ���ڰ� 1�� ���, ������ 0�� �� �� �ֱ� ������ N-1�� 0�� ������ ����.]	
		one_cnt[i] = zero_cnt[i - 1];		// [N��°�� ������ �ڸ��� 1�� ����, N-1��°�� 0�� ���� ��ŭ 1�� ���� �� �ִ�.]
		zero_cnt[i] = one_cnt[i - 1] + zero_cnt[i-1];		// [N��°�� ������ �ڸ��� 0�� ����, N-1��°�� 1�� ������ 0�� ���� ��ŭ 0�� ���� �� �ִ�.]
	}

	cout << memo[N] << endl;		// Output.
}