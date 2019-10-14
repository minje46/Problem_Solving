#include<iostream>
#include<memory.h>
#include<queue>

#define MAX 101

using namespace std;

const int dy[4] = { -1,1,0,0 };
const int dx[4] = { 0,0,-1,1 };

int N, M;							// N = The height of map.				M = The width of map.
int map[MAX][MAX];		// map = The memory of input data.
int cnt[MAX][MAX];		// cnt = The memoy of counts how many empty spaces are around cheese.
int total = 0, answer = 0;	// total = The total number of cheeses.			answer = The time to consume all of chesses as output.

void BFS()		// To figure out how many empty spaces are around cheese.
{
	bool visit[MAX][MAX];		// visit = The memory of visited or not.
	memset(visit, false, sizeof(visit));
	memset(cnt, 0, sizeof(cnt));

	queue<pair<int, int>> que;		
	que.push(make_pair(0, 0));		
	while (!que.empty())
	{
		auto cur = que.front();
		que.pop();

		for (int i = 0; i < 4; i++)
		{
			int ny = cur.first + dy[i];
			int nx = cur.second + dx[i];

			if (ny < 0 || ny >= N || nx < 0 || nx >= M)		// Overflow.
				continue;

			if (map[ny][nx] == 1)		// [Empty space 기준에서 상,하,좌,우 에 cheese가 있으면, count.]
				cnt[ny][nx] += 1;		

			else if (!visit[ny][nx])		// [Empty space 에서 상,하,좌,우 연결된 것만 bfs.]
			{									// [Cheese 내부에 있는 empty space는 search 하지 않게 된다.]
				que.push(make_pair(ny, nx));
				visit[ny][nx] = true;
			}
		}
	}
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);	cout.tie(0);

	cin >> N >> M;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			cin >> map[i][j];			// Input data.
			if (map[i][j] == 1)			// Total number of cheese.
				total += 1;
		}
	}

	while (total > 0)		// Untill all of chesses run out.
	{
		BFS();		// To search chees exists or not.
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < M; j++)
			{
				if (cnt[i][j] >= 2)		// [Cheese의 외부 접한 면의 수가 2 이상인 경우,]
				{
					map[i][j] = 0;
					total -= 1;
				}
			}
		}

		answer += 1;
	}

	cout << answer << endl;
}