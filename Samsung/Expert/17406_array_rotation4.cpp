#include<iostream>
#include<algorithm>
#include<memory.h>
#include<vector>
#include<queue>

#define MAX 51
#define INF 987654321

using namespace std;

const int CW[4][2] = {		// The {up,down,left,right} should arrange depends on length of square.
	{ -1,-1 },	// Left + Up.
	{-1,1},		// Right + Up.
	{1,1},		// Right + Down.
	{1,-1},		// Left + Down.
};

struct Distortion		// The memory of distortion data.	
{
	int y, x;				// Base coordinate.
	int len;				// The range of distortion.
};

int N, M, K;		// N = The height of map.		M = The width of map.			K = The number of rotation.
int original[MAX][MAX];		// original = The memory of original input data.
int map[MAX][MAX];			// map = The temporary memory of input data.
vector<Distortion> dist;		// dist = The memory of distortion data.
int answer = INF;					// answer = The minimum row sum value as output.
int order[MAX];					// order = The memory of random order of distortion to check every cases.
bool visit[MAX];					// visit = The memory of visited or not.

void Copy()		// To copy the original inputa data in temporary memory.
{
	memset(map, 0, sizeof(map));
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= M; j++)
			map[i][j] = original[i][j];
	}
}

int Row_sum()			// To calculate the minimum sum value each row.
{
	int result = INF;	// result = The memory for minimum sum value.

	for (int i = 1; i <= N; i++)
	{
		int sum = 0;
		for (int j = 1; j <= M; j++)
			sum += map[i][j];		// The sum value of row.

		result = min(result, sum);
	}

	return result;
}

void Space_distortion(int y, int x, int r)		// To do Clock Wise rotation from (y,x).
{
	for (int i = 1; i <= r; i++)
	{
		queue<int>que;
		que.push(map[y + (CW[0][0] * i)][x + (CW[0][1] * i)]);		// Start point. 
		for (int k = 0; k < 4; k++)		// [For each four diagonal points.]
		{
			int dpt_y = y + (CW[k][0] * i), dpt_x = x + (CW[k][1] * i);	// Each start point. [�� 4�𼭸��� �������� �ȴ�.]
			int dst_y = 0, dst_x = 0;

			if (k == 3)
				dst_y = y + (CW[0][0] * i), dst_x = x + (CW[0][1] * i);	// [��������� ���ƿ��� ���.]
			else
				dst_y = y + (CW[k + 1][0] * i), dst_x = x + (CW[k + 1][1] * i);		// [���� �𼭸��� ��������.]

			while (dpt_y != dst_y || dpt_x != dst_x)		// [Departure->Destination�� �Ǳ� ���� ������ ����.]
			{
				if (dpt_y - dst_y < 0)			// [Down �������� �̵��ϴ� ���.]
					dpt_y++;
				else if (dpt_y - dst_y > 0)		// [Up �������� �̵��ϴ� ���.]
					dpt_y--;

				if (dpt_x - dst_x < 0)			// [Right �������� �̵��ϴ� ���.]
					dpt_x++;
				else if (dpt_x - dst_x > 0)		// [Left �������� �̵��ϴ� ���.]
					dpt_x--;

				que.push(map[dpt_y][dpt_x]);		// [�� ĭ�� �и��°��̹Ƿ�, queue�� ����Ͽ� FIFO�� data ��������.]
				map[dpt_y][dpt_x] = que.front();		// [������ value�� queue�� ���������Ƿ�, data ����.]
				que.pop();		// [�������� ���� pop.]
			}						// [queue���� ���������� ���ƿԱ� ������, Up+Left�� value�� ����������, while�� �ȿ��� �̹� update�� ������ ������, ����.]
		}
	}
}

void DFS(int cnt)		// To do exhaustive search as permutation. [��� ����� ���� Ȯ���ϱ� ����.]
{
	if (cnt >= K)		// [K�� = ��� ���Ұ� order�� ��ġ �Ǿ��� ���, order�� �°� search.]
	{
		Copy();		// Set the basic array first. [Rotation�� �� ����, original map�� �ʿ�.]
		//answer = min(answer, Row_sum());			// To compare the original case.	[original map�� �񱳵� �ʿ䰡 �ִ��� ����.]
		for (int i = 0; i < dist.size(); i++)
			Space_distortion(dist[order[i]].y, dist[order[i]].x, dist[order[i]].len);
		//answer = min(answer, Row_sum());			// [��� distortion�� �̿��� �ʿ䰡 ���ٴ� ������ ������ ���� code.]
		answer = min(answer, Row_sum());
		return;
	}

	for (int i = 0; i < K; i++)		// [������ ��� ���� ��� ����� ���� Ȯ���ؾ� �ϱ⿡, �Ź� 0~K���� loop�� ������� ���� ��ȣ�� check���־�� �Ѵ�.]
	{
		if (!visit[i])	
		{
			visit[i] = true;			
			order[cnt] = i;			// [���� idx�� �´� order�� �ֱ� ����, cnt�� idx��Ż����.]
			DFS(cnt + 1);		
			visit[i] = false;
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
			cin >> original[i][j];		// Original input data.
	}

	for (int i = 0; i < K; i++)
	{
		int y, x, r;
		cin >> y >> x >> r;
		dist.push_back({ y, x, r });	// Distortion data.
	}

	DFS(0);		// To do Exhaustive search. [idx���� cnt�� ����Ͽ�, ������ �ƴ�, ��� ��츦 �� Ȯ���Ѵ�.]

	cout << answer << endl;		// Minimum sum value as output.
}