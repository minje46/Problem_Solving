#include<iostream>
#include<algorithm>
#include<memory.h>

using namespace std;

const int Mod = 1000000000;

int cache[10][101];

long long Stair_Num(int num, int len)			// To figure out the number of stari numbers.
{
	if (num < 0 || num > 9)			// Base case.
		return 0;

	int &answer = cache[num][len];		
	if (answer != -1)		
		return answer;
							// [+-1 ���̰� ���� stair number �̱� ������, num-1�� num+1�� ������ �̿��ؼ� ���� num�� ������ �ľ�.]	
	return answer = (Stair_Num(num - 1, len - 1) + Stair_Num(num + 1, len - 1)) % Mod;
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int N;				// N = The number of value's digits.
	cin >> N;

	memset(cache, -1, sizeof(cache));		// Initialize.
	for (int i = 0; i <= 9; i++)
		cache[i][1] = 1;				// The first case for memoization.

	int sum = 0;
	for (int i = 1; i <= 9; i++)
	{
		sum += Stair_Num(i, N);		// [�� �ڸ���(i)�� ������ stair number���� ���� ���.]
		sum %= Mod;	
	}

	cout << sum << endl;
}