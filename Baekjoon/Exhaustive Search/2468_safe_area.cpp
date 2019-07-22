#include<iostream>
#include<algorithm>
#include<memory.h>

#define MAX 101

using namespace std;

int N;									// N = The size of map.	
int map[MAX][MAX];			// The memory of map.
bool visit[MAX][MAX];			// Checking for visited or not.
int dy[4] = {-1, 1, 0, 0};		// Up, down, left, right.
int dx[4] = {0, 0, -1, 1};

void DFS(int y, int x, int height)		// To figure out whether there is path to move or not.
{
	for (int i = 0; i < 4; i++)
	{
		int ny = y + dy[i];		// Up, Down.
		int nx = x + dx[i];		// Left, Right.	

		if (ny < 0 || ny >= N || nx < 0 || nx >= N)		// Overflow area.
			continue;

		if(map[ny][nx] > height && !visit[ny][nx])
		{
			visit[ny][nx] = true;
			DFS(ny, nx, height);
		}
	}
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	int min_height = MAX, max_height = -1;		// [Min~Max height 까지 brute force로 모두 search 해야되므로, height 저장.]
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)		// Input of map.
		{										// Store the Min, Max height.
			cin >> map[i][j];
			min_height = min(min_height, map[i][j]);
			max_height = max(max_height, map[i][j]);
		}
	}
	
	int max_area = 1;					// max_area = The maximum count of safe area. [최대 안전 영역 개수.]
	for (int h = min_height; h < max_height; h++)		// [비가 오지 않을 경우, 최소 안전 영역의 개수가 1개이다?]
	{											// [The minimum value of rainfall is 1 인데..?]
		memset(visit, false, sizeof(visit));
		int cnt = 0;			
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				if (!visit[i][j] && map[i][j] > h)	// The possible area. [침수 되지 않는 높이와 아직 방문하지 않은 지역 탐색.]
				{
					visit[i][j] = true;
					cnt++;
					DFS(i, j, h);			// To figure out whether there is path to move or not.
				}
			}
		}
		max_area = max(max_area, cnt);			// Compare max area.
	}
	cout << max_area << endl;		// Output.
}