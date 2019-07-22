#include<iostream>
#include<algorithm>
#include<queue>
#include<string.h>
#include<cmath>

#define MAX 52

using namespace std;

int map[MAX][MAX];			// The memory of map.	
bool visit[MAX][MAX];			// The memory of visited.
int dx[4] = { 1, 0, -1, 0 };	// Rihgt, Down, Left, Up.
int dy[4] = { 0, 1, 0, -1 };
queue<pair<int, int>>uni;		// Union nations.
int N, L, R;			// N = The size of map.		L = The least criteria.		R = The most criteria.

bool BFS()		// To do exhaustive search on the map.
{
	bool flag = false;		// The memory of checking whether there is opened border or not. [Open 가능한 경계선 존재 여부를 위한 메모리.]
	queue<pair<int, int>>que;	// To do bfs with coordinates.	[BFS를 하기 위한 queue로서, 좌표를 저장.]

	for (int i = 1; i <= N; i++)		// i = y좌표.
	{
		for (int j = 1; j <= N; j++)	// j = x좌표.
		{
			if (visit[i][j])				// It's already visited area. [이미 방문된 국가.]
				continue;
											// [방문하지 않은 국가를 시작점으로 bfs 시작.]							
			int sum = map[i][j];	//	[현재 방문한 국가의 인구 수를 저장.]
			visit[i][j] = true;			// [현재 국가를 visit했다고 간주.]
			que.push({ i, j });		// For bfs.
			uni.push({ i, j });			// For nation's union.
			while (!que.empty())	// Until there is no more nations to access. [인접한 국가 중 방문이 가능한 국가가 없을 때 까지.]	
			{
				int idy = que.front().first;		// i = y좌표.
				int idx = que.front().second;		// j = x좌표. 이기 때문에...
				que.pop();

				for (int i = 0; i < 4; i++)	// Adjacent area to access.
				{
					int ny = idy + dy[i];		// right, down, left, up.
					int nx = idx + dx[i];
					if (ny<1 || ny >N || nx <1 || nx>N)	// Impossible area. [접근 불가능 범위(지역).]
						continue;
					else 
					{		// [방문하지 않은 국가이면서, 인접한 국가와 인구 수의 차이가 L~R 범위내에 포함되는 경우.]
						if (!visit[ny][nx] && L <= abs(map[idy][idx] - map[ny][nx]) && abs(map[idy][idx] - map[ny][nx]) <= R)
						{
							visit[ny][nx] = true;		// [인접한 국가를 방문했다고 간주.]
							que.push({ ny, nx });	// The coordinate of adjacent nation which is able to be included in nation's union.
							uni.push({ ny, nx });	// [연합 국가가 될 수 있는 인접한 국가의 좌표.]
							sum += map[ny][nx];	// [연합 국가의 총 인원 수.]
							flag = true;					// [경계선이 존재한다는 것을 의미.]
						}
					}
				}
			}
			// [(i,j) 좌표를 기준으로 경계선을 공유할 수 있는 국가가 있는지 판단하기 위한 while()을 수행.]
			int avg = sum / uni.size();		// [연합 국가의 평균 인원 수를 위한 계산.]
			while(!uni.empty())				// [연합 국가가 없더라도, (i,j) 자기 자신의 값을 가지는 연산이며, while()문이 수행되지 않기에 update가 되지 않는다.]
			{
				map[uni.front().first][uni.front().second] = avg;		// Update the union nation's population as average population.
				uni.pop();						// [연합 국가의 평균 인원 수로 업데이트.]
			}
		}
	}
	return flag;		// Return there is boundary which is able to be shared. [공유 가능한 경계선의 존재 유무를 return.]
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin >> N >> L >> R;
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++)
			cin >> map[i][j];		// Organize the map.

	int total = 0;						// The memory of total number of population movement.
	while (true)
	{
		memset(visit, false, sizeof(visit));		// Initialize the visit memory to do bfs multiple times. [BFS를 여러번 하기 위한, visit 초기화.]
		if (BFS())
			total++;						// The population movement was generated.
		else
			break;						// There is no border which was opened. [Open 가능한 국경선이 없는 경우.]
	}

	cout << total << endl;			// The total number of population movement's generation.
}