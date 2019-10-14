#include<iostream>
#include<algorithm>
#include<memory.h>

#define MAX 101

using namespace std;

const int tetris[13][4][2] =
{														// The whole of tetris block cases.
	{ { 0,0 },{ 0,1 } ,{ 1,0 } ,{ 1,1 } },		// '¤±'
{ { 0,0 },{ 0,1 } ,{ 0,2 } ,{ 0,3 } },	// '¤Ñ'
{ { 0,0 },{ 1,0 } ,{ 2,0 } ,{ 3,0 } },	// '¤Ó'
{ { 0,0 },{ 0,1 } ,{ 1,1 } ,{ 1,2 } },	// '¤©'
{ { 0,1 },{ 1,1 } ,{ 1,0 } ,{ 2,0 } },	// '¤© -> rotate'
{ { 0,0 },{ 0,1 } ,{ 0,2 } ,{ 1,2 } },	// '¤¡'
{ { 2,0 },{ 0,1 } ,{ 1,1 } ,{ 2,1 } },	// 'L' -> right rotate
{ { 0,0 },{ 1,0 } ,{ 1,1 } ,{ 1,2 } },	// '¤¤'
{ { 0,0 },{ 1,0 } ,{ 2,0 } ,{ 0,1 } },	// 'L' -> down side rotate
{ { 0,0 },{ 0,1 } ,{ 0,2 } ,{ 1,1 } },	// '¤Ì'
{ { 0,0 },{ 1,0 } ,{ 2,0 } ,{ 1,1 } },	// '¤¿'
{ { 0,0 },{ 0,1 } ,{ 0,2 } ,{ -1,1 } },	// '¤Ç'
{ { 0,0 },{ 0,1 } ,{ -1,1 } ,{ 1,1 } },	// '¤Ã'
};

int N;								// N = The size of map.
int map[MAX][MAX];		// map = The memory of input data.

int Simulation(int y, int x)		// To check all of cases in simulation.
{
	int res = -987654321;		// Basic state.

	for (int k = 0; k < 13; k++)	// All of cases.
	{
		int tot = 0, flag = 1;
		for (int i = 0; i < 4; i++)
		{
			int ny = y + tetris[k][i][0];
			int nx = x + tetris[k][i][1];

			if (ny < 0 || ny >= N || nx < 0 || nx >= N)		// Overflow.
			{
				flag--;
				break;
			}
			tot += map[ny][nx];
		}
		if (flag)		// Possible figure.
			res = max(res, tot);		// Compare the maximum sum.
	}
	return res;
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);	cout.tie(0);

	int t = 1;
	while (true)
	{
		cin >> N;
		if (N == 0)		// Break sign.
			break;
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
				cin >> map[i][j];		// Input data.
		}

		int answer = -987654321;	// answer = The maximum sum value as output.
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
				answer = max(answer, Simulation(i, j));		// From (0,0) to (N, N).
		}

		cout << t << ". " << answer << endl;		// Output.
		t += 1;
	}
}
