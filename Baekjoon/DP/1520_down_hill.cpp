#include<iostream>
#include<memory.h>

#define MAX 501

using namespace std;

int N, M;				// N = The width of map.		M = The height of map.
int map[MAX][MAX];		// map = The memory of original map.
int cache[MAX][MAX] = { 0, };		// cache = The memory of memoization.
int dy[4] = { 1,  0, 0, -1 };	// Down. Right.		[Because it is the way of end of right direction.]
int dx[4] = { 0, 1, -1, 0 };	// Left, Up.

int Down_hill(int y, int x)		// To figure out the way to destination.
{
	if (y == N && x == M)		// Base case.
		return 1;						// [(1,1)���� ����������, return�� (N,M)���� �Ǳ� ������ �Ųٷ� cache���� ä�����鼭 (1,1)�� �������� ����ȴ�.]

	int &answer = cache[y][x];
	if (answer != -1)				// Using memoization value.
		return answer;				// [Memo�� ���� ���� ���, �ش� ��(������ ����� ��)��ŭ ������ ���ָ� �ȴ�.]

	answer = 0;
	for (int i = 0; i < 4; i++)
	{
		int ny = y + dy[i];
		int nx = x + dx[i];

		if (ny <1 || ny > N || nx <1 || nx > M)			// Overflow.
			continue;

		if (map[y][x] > map[ny][nx])		// The condition for moving.
			answer += Down_hill(ny, nx);
	}
	return answer;
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> N >> M;
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= M; j++)
			cin >> map[i][j];			// Input of map.
	}

	memset(cache, -1, sizeof(cache));		// Initialization.

	cout <<	Down_hill(1, 1) << endl;			// Output of the result.	
}