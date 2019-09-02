#include<iostream>
#include<algorithm>
#include<queue>

#define MAX 11

using namespace std;

const int dy[4] = { 1,0,-1,0 };		// Up, Left.
const int dx[4] = { 0,1,0,-1 };		// Down, Right.

struct Beads		// The data of beads.
{
	int depth;		// The depth of dfs.
	int ry, rx;		// Location of red bead.
	int by, bx;		// Location of blue bead.
};

int N, M;							// N = The height of map.			M = The width of map.
int map[MAX][MAX];		// map = The memory of original input data.
bool visit[MAX][MAX][MAX][MAX];
pair<int, int> R, B, H;		// R, B = The red and blue bead's location.		H = The location of hole.
int answer = -1;				// answer = The minimum number of escape successfully as output.

void Roll(int &y, int &x, int dir)
{
	while (true)
	{
		y += dy[dir];
		x += dx[dir];

		if (map[y][x] == 1)
		{
			y -= dy[dir];
			x -= dx[dir];
			break;
		}
		else if (map[y][x] == -1)
			break;
	}
}

void BFS()
{
	queue<Beads>que;
	que.push({ 0,R.first,R.second,B.first,B.second });
	visit[R.first][R.second][B.first][B.second] = true;

	while (!que.empty())
	{
		auto cur = que.front();
		que.pop();

		if (cur.depth > 10)
			return;

		if (cur.ry == H.first && cur.rx == H.second)
		{
			answer = cur.depth;
			return;
		}

		for (int i = 0; i < 4; i++)
		{
			int ry = cur.ry;
			int rx = cur.rx;
			int by = cur.by;
			int bx = cur.bx;

			Roll(ry, rx, i);
			Roll(by, bx, i);

			if (by == H.first && bx == H.second)
				continue;

			if (ry == by && rx == bx)
			{
				switch (i)
				{
				case 0:
					cur.ry < cur.by ? ry-- : by--;
					break;
				case 1:
					cur.rx < cur.bx ? rx-- : bx--;
					break;
				case 2:
					cur.ry < cur.by ? by++ : ry++;
					break;
				case 3:
					cur.rx < cur.bx ? bx++ : rx++;
					break;
				default:
					break;
				}
			}

			if (!visit[ry][rx][by][bx])
			{
				Beads next = { cur.depth + 1, ry,rx,by,bx };
				que.push(next);
				visit[ry][rx][by][bx] = true;
			}
		}
	}
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> N >> M;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			char ch;
			cin >> ch;
			
			switch (ch)
			{
			case '#':	// Wall.
				map[i][j] = 1;
				break;
			case '.':		// Empty.
				map[i][j] = 0;
				break;
			case 'O':	// Hole.
				map[i][j] = -1;
				H = { i,j };
				break;
			case 'R':	// Red ball.
				R = { i,j };
				break;
			case 'B':	// Blue ball.
				B = { i,j };
				break;
			default:
				break;
			}
		}
	}

	BFS();

	cout << answer << endl;
}
