#include<iostream>
#include<algorithm>
#include<memory.h>
#pragma warning(disable:4996)

#define MAX 51

using namespace std;

int N, M;							// N = The height of map.			M = The width of map.
char map[MAX][MAX];	// map = The memory of input data.
int flag[MAX][3];			// flag = The number of each color blocks.	[0:W] [1:B] [2:R]
int answer;						// answer = The minimum number of blocks to repaint.

void Simulation()		// To compare all of cases.
{
	int tot = 0;
	for (int w = N - 2; w >= 1; w--)	// White.
	{												// From maximum(N-2) to minimum(1).
		int p_w = 0;
		for (int i = 1; i <= w; i++)
			p_w += M - flag[i][0];			// Repaint to white.

		for (int b = N - 1; b > w; b--)	// Blue.
		{											// From maximum(N-2) to minimum(1).	
			int p_b = 0;
			for (int j = w + 1; j <= b; j++)
				p_b += M - flag[j][1];		// Repaint to blue.

			int p_r = 0;
			for (int r = N; r > b; r--)		// Red.
				p_r += M - flag[r][2];		// Repaint to red.

			tot = p_w + p_b + p_r;
			answer = min(answer, tot);	// Compare the minimum blocks to repaint.

		}
	}
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);	cout.tie(0);

//	freopen("input.txt", "r", stdin);
	int test_case;
	cin >> test_case;
	for (int t = 1; t <= test_case; t++)
	{	// Initialization.
		memset(flag, 0, sizeof(flag));

		cin >> N >> M;
		for (int i = 1; i <= N; i++)
		{
			for (int j = 1; j <= M; j++)
			{
				cin >> map[i][j];			// Input data.
				if (map[i][j] == 'W')
					flag[i][0] += 1;			// White color.
				else if (map[i][j] == 'B')
					flag[i][1] += 1;			// Blue color.
				else
					flag[i][2] += 1;			// Red color.
			}
		}

		answer = N * M;			// Initialization.
		Simulation();				// Compare all of cases.
		cout << "#" << t << " " << answer << endl;		// Output.
	}
}