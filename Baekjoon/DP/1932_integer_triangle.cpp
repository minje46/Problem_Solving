#include<iostream>
#include<algorithm>
#include<memory.h>

#define MAX 501

using namespace std;
	
int N;										// N = The size of triangle.
long long map[2][MAX];			// map = The memory of triangle.
long long answer = 0;				// answer = The maximum sum value as output.

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);		cout.tie(0);

	memset(map, 0, sizeof(map));
	cin >> N;
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= i; j++)
		{
			cin >> map[1][j];			// Input of the current row.
			map[1][j] += max(map[0][j - 1], map[0][j]);		// Compare the value.
		}
		swap(map[0], map[1]);		// [input과 동시에 previous 값과 계산을 한다.] + [Each row의 수 만큼 map[0]에 저장하고 있도록 한다.]
	}

	for (int i = 1; i <= N; i++)
		answer = max(answer, map[0][i]);		// The maximum sum value in last row.
	cout << answer << endl;			// Output.
}