#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
#include<memory.h>

#define MAX 51
#define INF 987654321

using namespace std;

int N, M;														// N = The size of map.			M = The number of virus.
int answer = INF, tot_empty = 0;					// answer = The minimum time to spread out.		tot_empty = The total number of empty space.
int map[MAX][MAX], time[MAX][MAX];		// 	map = The memory of map.		time = The memory of time to spend spreading out.
vector<pair<int, int>> virus;							// virus = The memory of virus's location.	
int dy[4] = { -1,1,0,0 };								// Up, Down.
int dx[4] = { 0,0,-1,1 };								// Left, Right.
bool check[MAX] = { false, };						// check = The memory of virus's combination.

int BFS()			// To figure out the total time to spread out virus on the map.
{
	queue<pair<int, int>> que;
	for (int i = 0; i < virus.size(); i++)
	{
		if (check[i])		// The condition of combination.
		{
			que.push(make_pair(virus[i].first, virus[i].second));	// The list of virus activated.
			time[virus[i].first][virus[i].second] = 0;					// And it will spread out itself and starts at time 0.
		}
	}

	int sec = 0, tot_spread = 0;		// sec = The total seconds the virus spread out.		tot_spread = It counts the number of spread out on only empty area.
	while (!que.empty())
	{
		int y = que.front().first;
		int x = que.front().second;
		que.pop();

		for (int i = 0; i < 4; i++)
		{
			int ny = y + dy[i];
			int nx = x + dx[i];
			if (ny < 0 || ny >= N || nx < 0 || nx >= N)			// Overflow.
				continue;

			if (map[ny][nx] != 1 && time[ny][nx] == -1)		// The area is not wall and is possible to spread out.
			{																	// [벽이 아닌 공간이면서, [time=-1]은 아직 virus가 퍼지지 않은 곳.]
				que.push(make_pair(ny, nx));		// The new area to be spread.
				time[ny][nx] = time[y][x] + 1;		// Updates the time from now on.
				if (map[ny][nx] == 0)		// The case of the area is empty.
				{									// [기존에, 비활성화 virus가 있던 공간을 구분짓기 위해.]
					tot_spread++;				// Counts the time by spreaded.
					sec = time[ny][nx];		// The spread time should be counted on only empty area.
				}									// [Inactive virus가 active되는 것은 시간 소요X.]
			}
		}
	}
	if (tot_empty == tot_spread)			// When the whole of empty area was spread out by virus.
		return sec;
	else											// If not, it is impossible case.
		return INF;
}

void DFS(int idx, int cnt)		// To figure out each different combinations with controlling index and count.
{
	if (cnt == M)					// The condition of combination.
	{
		memset(time, -1, sizeof(time));		// Do initialize the time memory to compare with each different combinations.
		answer = min(answer, BFS());			// Store the only smaller time to spread out.
		return;
	}

	if (idx == virus.size())				// To avoid index overflow.
		return;

	check[idx] = true;			// Check the current index to make combination.
	DFS(idx + 1, cnt + 1);		// Controlling added index and count for combination.
	check[idx] = false;			// This index was used right before, so it should be changed as false.
	DFS(idx + 1, cnt);			// Controlling another index to make different combination compared to previous one.
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> N >> M;							// The size of map and number of virus.
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> map[i][j];				// The original map.
			if (map[i][j] == 0)
				tot_empty++;					// The total empty space.

			if (map[i][j] == 2)				// Store the location of virus.
				virus.push_back(make_pair(i, j));
		}
	}

	DFS(0, 0);					// Check the all cases based on combination.

	if (answer == INF)		// There is no way to spread out.	
		cout << -1 << endl;
	else							// The minimum time to spread out.
		cout << answer << endl;
}