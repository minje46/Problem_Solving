#include<iostream>
#include<memory.h>
#include<queue>

#define MAX 51
#define MASK 64
#define INF 987654321

using namespace std;

const int dy[4] = { -1,1,0,0 };
const int dx[4] = { 0,0,-1,1 };

struct location		// Queue data.
{
	int y, x;	// Location.
	int cnt;	// Movement.
	int key;	// Whether key has or not.
};

int N, M;										// N = The height of map.				M = The width of map.
char map[MAX][MAX];				// map = The memory of input data.
bool visit[MASK][MAX][MAX];		// visit = The memory of visited or not.
pair<int, int> dpt;						// dpt = The departure location.
int answer = INF;							// answer = The shortest way to escape as output.

void BFS()		// To figure out the shortest way to escape based on bfs.
{
	queue<location> que;
	que.push({ dpt.first, dpt.second, 0, 0 });
	while (!que.empty())
	{
		auto cur = que.front();
		que.pop();

		if (map[cur.y][cur.x] == '1')		// Base case. [Escape.]
		{
			answer = cur.cnt;
			return;
		}

		for (int i = 0; i < 4; i++)
		{
			int ny = cur.y + dy[i];
			int nx = cur.x + dx[i];

			if (ny < 0 || ny >= N || nx < 0 || nx >= M)		// Overflow.
				continue;

			if (!visit[cur.key][ny][nx] && map[ny][nx] != '#')		// Not visited yet. + Not wall.
			{
				if (map[ny][nx] >= 'a' && map[ny][nx] <= ' f')		// Key.
				{
					int k = cur.key | (1 << (int(map[ny][nx]) - 97));		// [해당 key를 (ny,nx) 좌표에서 얻었다는 것을 의미.]
					if (!visit[k][ny][nx])		// [a<<b : bit masking은 a를 b만큼 left shift 한다.]
					{									// [a~f를 0~5의 integer로 변환해서, bit masking 한다.]
						visit[cur.key][ny][nx] = true;	// [현재 key의 상태로 visit 한 것을 표시.]
						visit[k][ny][nx] = true;			// [key를 얻은 위치에서 visit을 체크/]
						que.push({ ny,nx,cur.cnt + 1, k });
					}
				}
				else if (map[ny][nx] >= 'A' && map[ny][nx] <= 'F')		// Door.
				{
					if (cur.key & 1 << (int(map[ny][nx]) - 65))	// [해당 door를 열 수 있는 key를 확인하기 위해 bit masking.]
					{										// [Or 연산을 통해 key가 존재하는지?(1) / 존재하지 않는지? (0) 을 파악.]
						visit[cur.key][ny][nx] = true;
						que.push({ ny,nx,cur.cnt + 1, cur.key });
					}
				}
				else			// Move.
				{
					visit[cur.key][ny][nx] = true;
					que.push({ ny,nx,cur.cnt + 1, cur.key });
				}
			}
		}
	}
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);	cout.tie(0);
	memset(visit, 0, sizeof(visit));

	cin >> N >> M;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			cin >> map[i][j];			// Input map data.
			if (map[i][j] == '0')			// Departure.
				dpt = { i,j };
		}
	}

	visit[0][dpt.first][dpt.second] = true;
	BFS();			// BFS algorithm.

	if (answer == INF)		// Impossible case.
		answer = -1;
	cout << answer << endl;		// Output.
}