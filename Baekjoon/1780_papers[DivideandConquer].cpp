#include<iostream>
#include<algorithm>
#include<cmath>
#include<vector>

#define MAX 2200

using namespace std;

int map[MAX][MAX];			// map = The memory of total map stored each number.
int answer[3] = { 0, };			// answer = The memory of counting each paper. [0] = paper value -1, [1] = paper value 0, [2] = paper value 1.

bool Same(int x, int y, int n)		// To figure out all of values inside area(x,y) are the same.
{
	for (int i = x; i < x + n; i++)
		for (int j = y; j < y + n; j++)
			if (map[x][y] != map[i][j])		// Compare the map[i][j] which is the first paper value and map[x][y].
				return false;

	return true;
}

void Divide(int x, int y, int n)		// To divide the square area within n area.
{
	if (Same(x, y, n))				// To check the area has same value or not.
	{										// [base case.]
		answer[map[x][y] + 1]++;
		return;
	}

	int k = n / 3;						// Set the smaller area	 with divided.
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			Divide(x + i * k, y + j * k, k);
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int N;				// N = The size of map.
	cin >> N;
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++)
			cin >> map[i][j];

	Divide(1, 1, N);

	for (int i = 0; i < 3; i++)
		cout << answer[i] << endl;
}