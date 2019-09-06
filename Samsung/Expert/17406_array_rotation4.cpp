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
			int dpt_y = y + (CW[k][0] * i), dpt_x = x + (CW[k][1] * i);	// Each start point. [각 4모서리가 시작점이 된다.]
			int dst_y = 0, dst_x = 0;

			if (k == 3)
				dst_y = y + (CW[0][0] * i), dst_x = x + (CW[0][1] * i);	// [출발점으로 돌아오는 경우.]
			else
				dst_y = y + (CW[k + 1][0] * i), dst_x = x + (CW[k + 1][1] * i);		// [다음 모서리가 도착지점.]

			while (dpt_y != dst_y || dpt_x != dst_x)		// [Departure->Destination이 되기 위해 점차적 진행.]
			{
				if (dpt_y - dst_y < 0)			// [Down 방향으로 이동하는 경우.]
					dpt_y++;
				else if (dpt_y - dst_y > 0)		// [Up 방향으로 이동하는 경우.]
					dpt_y--;

				if (dpt_x - dst_x < 0)			// [Right 방향으로 이동하는 경우.]
					dpt_x++;
				else if (dpt_x - dst_x > 0)		// [Left 방향으로 이동하는 경우.]
					dpt_x--;

				que.push(map[dpt_y][dpt_x]);		// [한 칸씩 밀리는것이므로, queue를 사용하여 FIFO로 data 변경해줌.]
				map[dpt_y][dpt_x] = que.front();		// [기존의 value는 queue에 저장했으므로, data 변경.]
				que.pop();		// [변경해준 값은 pop.]
			}						// [queue에는 시작점으로 돌아왔기 때문에, Up+Left의 value가 존재하지만, while문 안에서 이미 update가 끝났기 때문에, 버림.]
		}
	}
}

void DFS(int cnt)		// To do exhaustive search as permutation. [모든 경우의 수를 확인하기 위함.]
{
	if (cnt >= K)		// [K개 = 모든 원소가 order에 배치 되었을 경우, order에 맞게 search.]
	{
		Copy();		// Set the basic array first. [Rotation할 때 마다, original map이 필요.]
		//answer = min(answer, Row_sum());			// To compare the original case.	[original map이 비교될 필요가 있는지 여부.]
		for (int i = 0; i < dist.size(); i++)
			Space_distortion(dist[order[i]].y, dist[order[i]].x, dist[order[i]].len);
		//answer = min(answer, Row_sum());			// [모든 distortion을 이용할 필요가 없다는 기존의 문제를 위한 code.]
		answer = min(answer, Row_sum());
		return;
	}

	for (int i = 0; i < K; i++)		// [순서에 상관 없이 모든 경우의 수를 확인해야 하기에, 매번 0~K까지 loop로 사용하지 않은 번호를 check해주어야 한다.]
	{
		if (!visit[i])	
		{
			visit[i] = true;			
			order[cnt] = i;			// [현재 idx에 맞는 order를 넣기 위해, cnt를 idx대신사용함.]
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

	DFS(0);		// To do Exhaustive search. [idx없이 cnt만 사용하여, 조합이 아닌, 모든 경우를 다 확인한다.]

	cout << answer << endl;		// Minimum sum value as output.
}