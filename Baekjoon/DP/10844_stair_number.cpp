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
							// [+-1 차이가 나는 stair number 이기 때문에, num-1과 num+1의 개수를 이용해서 현재 num의 개수를 파악.]	
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
		sum += Stair_Num(i, N);		// [각 자리수(i)로 끝나는 stair number들의 수를 계산.]
		sum %= Mod;	
	}

	cout << sum << endl;
}