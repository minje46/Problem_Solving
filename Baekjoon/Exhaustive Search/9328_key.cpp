#include<iostream>
#include<memory.h>
#include<queue>
#include<string>

#define MAX 105

using namespace std;

const int dy[4] = { -1,1,0,0 };
const int dx[4] = { 0,0,-1,1 };

int H, W;						// H = The height of map.         W = The width of map.
char map[MAX][MAX];	// map = The memory of input data.
bool visit[MAX][MAX];    // visit = The memory of visited or not.
bool key[26];					// key = The key to open the door.
int answer = 0;				// answer = The number of documents as output.
bool flag = false;				// flag = The flag for any change or not.

void BFS(int y, int x)		// To figure out there is any key to gain or document.
{
	queue<pair<int, int>> que;
	que.push(make_pair(y, x));
	visit[y][x] = true;
	while (!que.empty())
	{
		auto cur = que.front();
		que.pop();

		if (map[cur.first][cur.second] == '$')		// Document.
		{
			map[cur.first][cur.second] = '.';			// To avoid duplication.
			answer += 1;										// The number of document.
			flag = true;											// Change arise.
		}
		for (int i = 0; i < 4; i++)
		{
			int ny = cur.first + dy[i];
			int nx = cur.second + dx[i];

			if (ny < 0 || ny > H + 1 || nx < 0 || nx > W + 1)		// Overflow.
				continue;

			if (!visit[ny][nx] && map[ny][nx] != '*')		// Not visit yet. + Not wall.
			{
				char ch = map[ny][nx];			// Door or Key.			
				if (ch >= 'A' && ch <= 'Z')		// Door.
				{
					if (!key[ch-65])					// Key exists?
						continue;
				}
				else if (ch >= 'a' && ch <= 'z')	// Key.
				{
					if (!key[ch-97])					// Not possess.
					{
						key[ch-97] = true;			// Key get.
						flag = true;						// Change arise.
					}
				}
				que.push(make_pair(ny, nx));	
				visit[ny][nx] = true;
			}
		}
	}
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);   cout.tie(0);

	int test_case;
	cin >> test_case;
	for (int t = 1; t <= test_case; t++)
	{   // Initialization.
		answer = 0;									
		memset(key, false, sizeof(key));

		cin >> H >> W;
		for (int i = 1; i <= H; i++)
		{
			for (int j = 1; j <= W; j++)
				cin >> map[i][j];			// Input data.
		}
		for (int i = 0; i <= H + 1; i++)		// Make a outside.
		{
			map[i][0] = '.';
			map[i][W + 1] = '.';
		}
		for (int j = 0; j <= W + 1; j++)
		{
			map[0][j] = '.';
			map[H + 1][j] = '.';
		}
		string str;
		cin >> str;								// Input key.
		for (int i = 0; i < str.length(); i++)
		{
			if (str[i] != '0')					
				key[str[i]-97] = true;	
		}

		while (true)
		{
			flag = false;
			memset(visit, false, sizeof(visit));
			BFS(0, 0);		// To do bfs.				

			if (!flag)			// To avoid infinite loop.
				break;
		}
		cout << answer << endl;		// Output.
	}
}