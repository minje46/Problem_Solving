#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>

#define MAX 51

using namespace std;

struct dust						// dust = The memory of original dust data. That's because dust spread out  at a time. 
{
	int y, x;
	int key;
};

int R, C, T;						// R = The size of height.		C = The size of width.		T = The total time.
int map[MAX][MAX];		// map = The memory of cleaner and particulate matter's map.
int dy[4] = { -1,1,0,0 };	// Up, Down.
int dx[4] = { 0,0,-1,1 };	// Left, Right.
pair<int, int>cleaner[2];	// cleaner = The location of air cleaner.

void Refresh()			// To circulate dust in CCW and CW direction.
{
	int k = 0;			// k = The index of air cleaner.	
	while (k < 2)
	{
		queue<int> que;		// The temporary memory of original dust data before sliding.
		que.push(0);
		// Right. [CCW와 CW 모두 right direction으로 시작하는 것은 동일.]
		for (int x = cleaner[k].second + 1; x <= C; x++)		// Keep the original data in queue.
			que.push(map[cleaner[k].first][x]);
		for (int x = cleaner[k].second + 1; x <= C; x++)		// Insert the (index + 1)'s data based on queue.
		{																		// [queue에 한 개가 추가적으로 저장되어 있기 때문에, sliding처럼 대입된다.]	
			map[cleaner[k].first][x] = que.front();
			que.pop();
		}

		if (k == 0)		// The first case. -> CCW ventilation.
		{
			for (int y = cleaner[k].first - 1; y >= 1; y--)		// Up
				que.push(map[y][C]);
			for (int y = cleaner[k].first - 1; y >= 1; y--)
			{
				map[y][C] = que.front();
				que.pop();
			}

			for (int x = C - 1; x >= 1; x--)		// Left.
				que.push(map[1][x]);
			for (int x = C - 1; x >= 1; x--)
			{
				map[1][x] = que.front();
				que.pop();
			}

			for (int y = 2; y < cleaner[k].first; y++)		// Down
				que.push(map[y][1]);
			for (int y = 2; y < cleaner[k].first; y++)
			{
				map[y][1] = que.front();
				que.pop();
			}
		}

		else						// The second case. -> CW ventilation.
		{
			for (int y = cleaner[k].first + 1; y <= R; y++)		// Down.
				que.push(map[y][C]);
			for (int y = cleaner[k].first + 1; y <= R; y++)
			{
				map[y][C] = que.front();
				que.pop();
			}

			for (int x = C - 1; x >= 1; x--)				// Left.
				que.push(map[R][x]);
			for (int x = C - 1; x >= 1; x--)
			{
				map[R][x] = que.front();
				que.pop();
			}

			for (int y = R - 1; y > cleaner[k].first; y--)		// Up
				que.push(map[y][1]);
			for (int y = R - 1; y > cleaner[k].first; y--)
			{
				map[y][1] = que.front();
				que.pop();
			}
		}
		k++;
	}
}

void Pollution()			// To spread out dust at the same time.
{
	queue<dust>que;		// To store the original dust data.	
	for (int i = 1; i <= R; i++)
	{
		for (int j = 1; j <= C; j++)
			if (map[i][j] >= 5)			// If the value is smaller than 5, it doesn't be changed at all.
				que.push({ i,j , map[i][j] });
	}

	while (!que.empty())		// Spread out the whole of dust.
	{
		auto cur = que.front();
		que.pop();

		int cnt = 0;			// cnt = Count the number of spraeded.			
		int flow = cur.key / 5;		// The value of spreaded.
		for (int i = 0; i < 4; i++)
		{
			int ny = cur.y + dy[i];
			int nx = cur.x + dx[i];

			if (ny <1 || ny>R || nx<1 || nx>C)		// Overflow.
				continue;

			if (map[ny][nx] != -1)			// Except air cleaner zone.
			{
				map[ny][nx] += flow;		// Spreading.
				cnt++;							// Counting the number.
			}
		}
		map[cur.y][cur.x] -= (flow * cnt);		// Reorganize the dust value.
	}
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int k = 0;		// For cleaner index.
	cin >> R >> C >> T;
	for (int i = 1; i <= R; i++)
	{
		for (int j = 1; j <= C; j++)
		{
			cin >> map[i][j];
			if (map[i][j] == -1)			// The location of Air cleaner.
			{
				cleaner[k].first = i;
				cleaner[k++].second = j;
			}
		}
	}


	while (T--)			// Time flow.		
	{
		Pollution();		// To spread out the particulate matters.
		Refresh();		// To operate air cleaner.
	}

	int answer = 0;
	for (int i = 1; i <= R; i++)
	{
		for (int j = 1; j <= C; j++)
			if (map[i][j] != -1)
				answer += map[i][j];
	}
	cout << answer << endl;

}