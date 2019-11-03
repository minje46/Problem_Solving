#include<iostream>
#include<memory.h>
#include<vector>
#include<queue>

#define MAX 52

using namespace std;

const int dy[4] = { -1,1,0,0 };
const int dx[4] = { 0,0,-1,1 };

struct rotation		// The data of rotation.
{
	int idx;			// The index of disk.
	int dir;			// Direction to rotate. [0 : CW] [1 : CCW]
	int range;		// Range to rotate.
};

int N, M, T;					// N = The height of map.			M = The width of map.				T = The number of rotation.
int map[MAX][MAX];	// map = The memory of input data.
vector<rotation> vc;		// vc = The memory of roation data.
bool flag;					// flag = The boolean value to distinguish duplication is or not.
int answer;					// answer = The total sum value as output.

int Sum()		// To calculate the total sum.
{
	int tot = 0;
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= M; j++)
			tot += map[i][j];
	}
	return tot;
}

void CW(int idx, int range)		// To rotate clock wise.
{
	for (int r = 0; r < range; r++)
	{
		for (int i = 1; i <= N; i++)
		{
			if (i % idx != 0)
				continue;

			queue<int>que;
			que.push(map[i][1]);		// First one.
			for (int j = 2; j <= M; j++)
			{
				que.push(map[i][j]);	// Swap.
				map[i][j] = que.front();
				que.pop();
			}
			map[i][1] = que.front();	// Last one.
		}
	}
}

void CCW(int idx, int range)		// To rotate counter clock wise.
{
	for (int r = 0; r < range; r++)
	{
		for (int i = 1; i <= N; i++)
		{
			if (i%idx != 0)
				continue;
			queue<int>que;
			que.push(map[i][M]);		// First one.
			for (int j = M - 1; j >= 1; j--)
			{
				que.push(map[i][j]);	// Swap.
				map[i][j] = que.front();
				que.pop();
			}
			map[i][M] = que.front();	// Last one.
		}
	}
}

void Duplication()		// To figure out the duplicate value with neighbors.
{
	bool check[MAX][MAX];
	memset(check, false, sizeof(check));

	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= M; j++)
		{
			for (int k = 0; k < 4; k++)
			{
				int ny = i + dy[k];
				int nx = j + dx[k];

				if (ny < 1 || ny > N || nx < 1 || nx > M)		// Overflow.
				{
					if (ny < 1 || ny > N)
						continue;
					else if (nx < 1)
						nx = M;
					else
						nx = 1;
				}

				if (map[i][j] == map[ny][nx])		// Adjacent four directions.
				{
					check[i][j] = true;
					check[ny][nx] = true;
				}
			}
		}
	}

	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= M; j++)
		{
			if (check[i][j] && map[i][j] != 0)
			{
				flag = true;
				map[i][j] = 0;
			}
		}
	}

}

void Arrange()			// To rearrange value based on average.
{
	int tot = 0, cnt = 0;
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= M; j++)
		{
			if (map[i][j] != 0)
			{
				tot += map[i][j];
				cnt += 1;
			}
		}
	}
	
	double avg;
	if (cnt > 0)
		avg = (double)tot / cnt;
	
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= M; j++)
		{
			if (map[i][j] == 0)
				continue;

			if (map[i][j] < avg)
				map[i][j] += 1;
			else if (map[i][j] > avg)
				map[i][j] -= 1;
		}
	}
}

void Simulation()		// To do disk rotation. [Rotation / Duplication / Arrange.]
{
	for (int i = 0; i < vc.size(); i++)
	{
		int idx = vc[i].idx;
		int dir = vc[i].dir;
		int range = vc[i].range;

		if (dir == 0)		// CW rotation.
			CW(idx, range);
		else				// CCW rotation.
			CCW(idx, range);

		flag = false;
		Duplication();		// Check duplication.
		if (!flag)
			Arrange();		// Arrange the map value.
	}
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);	cout.tie(0);

	cin >> N >> M >> T;
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= M; j++)
			cin >> map[i][j];			// Input map data.
	}
	for (int i = 0; i < T; i++)
	{
		int x, d, k;
		cin >> x >> d >> k;				// Input rotation data.
		vc.push_back({ x ,d,k });
	}

	Simulation();			// Do simulation.
	answer = Sum();		// Sum value.
	cout << answer << endl;			// Output.
}