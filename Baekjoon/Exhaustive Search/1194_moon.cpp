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
					int k = cur.key | (1 << (int(map[ny][nx]) - 97));		// [�ش� key�� (ny,nx) ��ǥ���� ����ٴ� ���� �ǹ�.]
					if (!visit[k][ny][nx])		// [a<<b : bit masking�� a�� b��ŭ left shift �Ѵ�.]
					{									// [a~f�� 0~5�� integer�� ��ȯ�ؼ�, bit masking �Ѵ�.]
						visit[cur.key][ny][nx] = true;	// [���� key�� ���·� visit �� ���� ǥ��.]
						visit[k][ny][nx] = true;			// [key�� ���� ��ġ���� visit�� üũ/]
						que.push({ ny,nx,cur.cnt + 1, k });
					}
				}
				else if (map[ny][nx] >= 'A' && map[ny][nx] <= 'F')		// Door.
				{
					if (cur.key & 1 << (int(map[ny][nx]) - 65))	// [�ش� door�� �� �� �ִ� key�� Ȯ���ϱ� ���� bit masking.]
					{										// [Or ������ ���� key�� �����ϴ���?(1) / �������� �ʴ���? (0) �� �ľ�.]
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