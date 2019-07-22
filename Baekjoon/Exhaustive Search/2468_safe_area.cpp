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
	int min_height = MAX, max_height = -1;		// [Min~Max height ���� brute force�� ��� search �ؾߵǹǷ�, height ����.]
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
	
	int max_area = 1;					// max_area = The maximum count of safe area. [�ִ� ���� ���� ����.]
	for (int h = min_height; h < max_height; h++)		// [�� ���� ���� ���, �ּ� ���� ������ ������ 1���̴�?]
	{											// [The minimum value of rainfall is 1 �ε�..?]
		memset(visit, false, sizeof(visit));
		int cnt = 0;			
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				if (!visit[i][j] && map[i][j] > h)	// The possible area. [ħ�� ���� �ʴ� ���̿� ���� �湮���� ���� ���� Ž��.]
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