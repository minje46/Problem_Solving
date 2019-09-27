#include<iostream>
#include<queue>

#define MAX 301

using namespace std;

const int dy[3] = { 1,1,0 };
const int dx[3] = { 0, 1,1 };

int N, M, R;		// N = The height of map.			M = The width of map.				R = The number of rotation.
int map[MAX][MAX];		// map = The memory of original input data.

void Rotation()		// To rotate the whole of 2 dimension array in counter clock wise.
{
	int k = min(N, M) / 2;		// k = The number of rotate on the array.
	int s_y = 0, e_y = N - 1, s_x = 0, e_x = M - 1;			// The index of start and end coordinate.
	for (int s = 0; s < k; s++)
	{
		pair<int, int> dpt = { s,s };	// From (0,0) to (k-1, k-1).
		queue<int> que;
		que.push(map[s][s]);			// Start position.
		for (int d = 0; d < 4; d++)		// Four directions.
		{
			int r_y = e_y - s_y;		// The range of y.
			int r_x = e_x - s_x;		// The range of x.
			pair<int, int> dst;			// Destination.
			if (d == 3)					// Return to start point.
				dst = { s,s };
			else
				dst = { s + (dy[d] * r_y), s + (dx[d] * r_x) };

			while (dpt.first != dst.first || dpt.second != dst.second)		// Until arrived.
			{
				if (dst.first - dpt.first > 0)		// Go down.
					dpt.first++;
				if (dst.first - dpt.first < 0)		// Go up.
					dpt.first--;

				if (dst.second - dpt.second > 0)		// Go right.
					dpt.second++;
				if (dst.second - dpt.second < 0)		// Go left.
					dpt.second--;

				que.push(map[dpt.first][dpt.second]);
				map[dpt.first][dpt.second] = que.front();		// Shift the value.
				que.pop();
			}
		}
		s_y += 1, s_x += 1;		// [Square가 대각선 모양으로 
		e_y -= 1, e_x -= 1;		// 내부의 위치 조정 되기 때문.]
	}
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> N >> M >> R;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
			cin >> map[i][j];					// Input.
	}

	for (int i = 0; i < R; i++)
		Rotation();									// Rotation.

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
			cout << map[i][j] << " ";			// Output.
		cout << endl;
	}
}