// DFS (Time out)
/*
#include<iostream>
#include<stdio.h>
#include<vector>
#include<stack>
#pragma warning(disable:4996)

using namespace std;

int N, M;									// N = height.				M = width.
int result = 10000;
vector<pair<int, int>> stk;			// stk = stack to save the visited coordinate.

bool Visited(int x, int y)
{
	for (int i = 0; i < stk.size(); i++)
		if (stk[i].first == x && stk[i].second == y)
			return true;

	return false;
}

void DFS(int **arr, int x, int y, int pass)
{
	stk.push_back({ x,y });			// visited this coordinate.
	pass++;							// counting the pass.

	if (x == N && y == M)			// get destination.
	{
		if (result > pass)
			result = pass;
		
		stk.pop_back();			// If it is in the stack, other way can't be searched because of Visted condition.
		return;
	}

	if (y + 1 <= M && arr[x][y + 1] == 1 && !Visited(x, y + 1))		// right.
		DFS(arr, x, y + 1, pass);

	if (x + 1 <= N && arr[x + 1][y] == 1 && !Visited(x + 1, y))		// down.
		DFS(arr, x + 1, y, pass);

	if (x - 1 >= 1 && arr[x - 1][y] == 1 && !Visited(x - 1, y))		// up.
		DFS(arr, x - 1, y, pass);

	if (y - 1 >= 1 && arr[x][y - 1] == 1 && !Visited(x, y - 1))		// left.
		DFS(arr, x, y - 1,pass);
}

int main(void)
{
	scanf("%d %d", &N, &M);

	int **input = new int *[N];
	for (int i = 1; i <= N; i++)
	{
		input[i] = new int[M];
		for (int j = 1; j <= M; j++)
			scanf("%1d", &input[i][j]);
	}

	DFS(input, 1, 1, 0);

	if (result != 10000)
		printf("%d\n", result);
	else
		printf("0\n");
}
*/

// BFS
#pragma warning(disable:4996)
#include<iostream>
#include<queue>
#include<cstring>

using namespace std;

int N, M;											// N = height.				M = width.
int **maze, **visited;						// maze = The N*M size maze.			visited = The bucket to check visited or not.
int dx[] = { 0, 1, 0, -1};					// The 'x' points can move. (Down, Right, Up, Left)
int dy[] = {-1, 0, 1, 0};					// The 'y' points can move. (Down, Right, Up, Left)

int BFS()
{
	queue<pair<int, int>> que;

	que.push(make_pair(0, 0));							// Start point.
	visited[0][0] = 1;										// With visited true.	
	while (!que.empty())
	{
		int cur_y = que.front().first;						// N is height.
		int cur_x = que.front().second;					// M is width.
		que.pop();

		if (cur_y == N - 1 && cur_x == M - 1)
			return visited[N - 1][M - 1];

		for (int i = 0; i < 4; i++)
		{
			int next_y = cur_y + dx[i];
			int next_x = cur_x + dy[i];

			if (0 <= next_y && next_y < N && 0 <= next_x && next_x < M)			// Check the next point is valid or not.
			{																								// [다음 좌표가 유효한지 overflow 여부 체크.]		
				if (!visited[next_y][next_x] && maze[next_y][next_x])					// Check visited or not and maze is able to pass through or not.
				{																							// [Visited는 0으로 초기화 되어 있기때문에, count 증가로 방문 여부 확인 가능.]	
					que.push(make_pair(next_y, next_x));
					visited[next_y][next_x] = visited[cur_y][cur_x] + 1;					// [현재 node의 다음 level에 +1로 count 해주는 것.]
				}
			}
		}
	}
}

int main(void)
{
	scanf("%d %d", &N, &M);

	maze = new int *[N];
	visited = new int *[N];
	for (int i = 0; i < N; i++)
	{
		maze[i] = new int[M];
		visited[i] = new int[M];
		for (int j = 0; j < M; j++)
			scanf("%1d", &maze[i][j]);
		memset(visited[i], 0, sizeof(visited)*M);
	}

	printf("%d \n",BFS());
}