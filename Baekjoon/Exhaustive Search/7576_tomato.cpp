#include<iostream>
#include<vector>
#include<queue>

using namespace std;

int Day = 0;										// Count each day.
queue<pair<int, int>> que;					// queue helps it is possible to read in bfs search.
vector<pair<int, int>> rippen;					// It saves the result of coordinate in Search function.

void Search(int **arr, int M, int N, int value)		// Search the coordinate if value exists.
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			if (arr[i][j] == value)
				rippen.push_back({ i,j });
		}
	}
}

void BFS(int **arr, int M, int N)
{			
	int term, count = 0;				// term = It saves the size of queue after checking adjacent node exists or not in each step.
										// It is for counting day. [while문이 queue.empty조건으로 돌아가기 때문에, 날짜를 counting하기 위한 조건이 필요.]
	
	for (int i = 0; i < rippen.size(); i++)		// At first time, push the origin coordinate of rippen tomato.
		que.push({ rippen[i].first, rippen[i].second });

	term = que.size();				//[term==count라는 것이, 한 step(level)이 search되었다고 볼 수 있다.]
	while (!que.empty())
	{
		if (term == count)			// It represents each step of bfs search.
		{
			Day++;
			count = 0;				 
			term = que.size();		
		}

		int x = que.front().first;
		int y = que.front().second;
		
		// Check adjacent node exists or not.
		if (y - 1 >= 0 && arr[x][y - 1] == 0)			// left
		{
			arr[x][y - 1] = 1;
			que.push({ x,y - 1 });
		}

		if (y + 1 <= M - 1 && arr[x][y + 1] == 0)			// right
		{
			arr[x][y + 1] = 1;
			que.push({ x,y + 1 });
		}
		if (x - 1 >= 0 && arr[x - 1][y] == 0)			// up
		{
			arr[x - 1][y] = 1;
			que.push({ x - 1,y });
		}
		if (x + 1 <= N - 1 && arr[x + 1][y] == 0)			// down
		{
			arr[x + 1][y] = 1;
			que.push({ x + 1,y });
		}

		que.pop();		// Checking adjacent node is finished above, it should be popped. 
		count++;			// If there is nothing to fit above conditions, it should be popped as well.
	}
	rippen.clear();		// It is for using Search function again.
}

int main(void)
{
	std::ios_base::sync_with_stdio(false);

	int M, N;					// M = width.		N = height.
	cin >> M >> N;

	int **input = new int *[N];		// Allocate two-dimension array dynamically.
	for (int i = 0; i < N; i++)
	{
		input[i] = new int[M];
		for (int j = 0; j < M; j++)
			cin >> input[i][j];
	}

	Search(input, M, N, 1);			// Search the coordinate of rippen tomato.(value = 1)

	//	for (int i = 0; i < rippen.size(); i++)
	//		cout << "(" << rippen[i].first << "," << rippen[i].second << ")" << endl;

	BFS(input, M, N);					// Do bfs searching.

	Search(input, M, N, 0);			// Search the coordinate of unrippen tomato.(value = 0)
											// Is there any unrippen tomato, doing bfs search is impossible.
	if (rippen.empty())					// The result of coordinate is stored in rippen vector.
		cout << Day << "\n";			// Judging with rippen vector.
	else
		cout << -1 << "\n";
}