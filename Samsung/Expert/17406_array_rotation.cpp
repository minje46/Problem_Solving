#include<iostream>
#include<algorithm>
#include<memory.h>
#include<vector>
#include<queue>
#include<cmath>

#define MAX 51

using namespace std;

const int CW[8][2] = {		// The {up,down,left,right} should arrange depends on length of square.
	{-1,-1},	// Left + Up.
	{-1,0},		// Up.
	{-1,1},		// Right + Up.
	{0,1},		//	Right.
	{1,1},		// Right + Down.
	{1,0},		// Down.	
	{1,-1},		// Left + Down.
	{0,1}			// Left.
};

struct Distortion
{
	int y, x;
	int len;
};

int N, M, K;		// N = The height of map.		M = The width of map.			K = The number of rotation.
int original[MAX][MAX];		// original = The memory of original input data.
int map[MAX][MAX];			// map = The temporary memory of input data.
vector<Distortion> dist;
int answer = 0;

void Copy()		// To copy the original inputa data in temporary memory.
{
	memset(map, 0, sizeof(map));
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= M; j++)
			map[i][j] = original[i][j];
	}
}

void Space_distortion(int y, int x, int r)
{
	queue<int>que;

	for (int i = 1; i <= r; i++)
	{
		for (int k = 0; k < 8; k++)
		{
			int ny = y + CW[k][0];
			int nx = x + CW[k][1];
			que.push(map[ny][nx]);		
		}
	}
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> N >> M >> K;
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= M; j++)
			cin >> original[i][j];
	}

	for (int i = 0; i < K; i++)
	{
		int r, c, s;
		cin >> r >> c >> s;
		dist.push_back({ r,c, s });
	}

	Space_distortion();

	cout << answer << endl;
}