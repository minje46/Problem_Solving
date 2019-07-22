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
	bool flag = false;		// The memory of checking whether there is opened border or not. [Open ������ ��輱 ���� ���θ� ���� �޸�.]
	queue<pair<int, int>>que;	// To do bfs with coordinates.	[BFS�� �ϱ� ���� queue�μ�, ��ǥ�� ����.]

	for (int i = 1; i <= N; i++)		// i = y��ǥ.
	{
		for (int j = 1; j <= N; j++)	// j = x��ǥ.
		{
			if (visit[i][j])				// It's already visited area. [�̹� �湮�� ����.]
				continue;
											// [�湮���� ���� ������ ���������� bfs ����.]							
			int sum = map[i][j];	//	[���� �湮�� ������ �α� ���� ����.]
			visit[i][j] = true;			// [���� ������ visit�ߴٰ� ����.]
			que.push({ i, j });		// For bfs.
			uni.push({ i, j });			// For nation's union.
			while (!que.empty())	// Until there is no more nations to access. [������ ���� �� �湮�� ������ ������ ���� �� ����.]	
			{
				int idy = que.front().first;		// i = y��ǥ.
				int idx = que.front().second;		// j = x��ǥ. �̱� ������...
				que.pop();

				for (int i = 0; i < 4; i++)	// Adjacent area to access.
				{
					int ny = idy + dy[i];		// right, down, left, up.
					int nx = idx + dx[i];
					if (ny<1 || ny >N || nx <1 || nx>N)	// Impossible area. [���� �Ұ��� ����(����).]
						continue;
					else 
					{		// [�湮���� ���� �����̸鼭, ������ ������ �α� ���� ���̰� L~R �������� ���ԵǴ� ���.]
						if (!visit[ny][nx] && L <= abs(map[idy][idx] - map[ny][nx]) && abs(map[idy][idx] - map[ny][nx]) <= R)
						{
							visit[ny][nx] = true;		// [������ ������ �湮�ߴٰ� ����.]
							que.push({ ny, nx });	// The coordinate of adjacent nation which is able to be included in nation's union.
							uni.push({ ny, nx });	// [���� ������ �� �� �ִ� ������ ������ ��ǥ.]
							sum += map[ny][nx];	// [���� ������ �� �ο� ��.]
							flag = true;					// [��輱�� �����Ѵٴ� ���� �ǹ�.]
						}
					}
				}
			}
			// [(i,j) ��ǥ�� �������� ��輱�� ������ �� �ִ� ������ �ִ��� �Ǵ��ϱ� ���� while()�� ����.]
			int avg = sum / uni.size();		// [���� ������ ��� �ο� ���� ���� ���.]
			while(!uni.empty())				// [���� ������ ������, (i,j) �ڱ� �ڽ��� ���� ������ �����̸�, while()���� ������� �ʱ⿡ update�� ���� �ʴ´�.]
			{
				map[uni.front().first][uni.front().second] = avg;		// Update the union nation's population as average population.
				uni.pop();						// [���� ������ ��� �ο� ���� ������Ʈ.]
			}
		}
	}
	return flag;		// Return there is boundary which is able to be shared. [���� ������ ��輱�� ���� ������ return.]
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
		memset(visit, false, sizeof(visit));		// Initialize the visit memory to do bfs multiple times. [BFS�� ������ �ϱ� ����, visit �ʱ�ȭ.]
		if (BFS())
			total++;						// The population movement was generated.
		else
			break;						// There is no border which was opened. [Open ������ ���漱�� ���� ���.]
	}

	cout << total << endl;			// The total number of population movement's generation.
}