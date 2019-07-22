#include<iostream>
#include<queue>
#include<vector>
#include<tuple>

using namespace std;
typedef tuple<int, int, int> triple;

int Day = 0;											// Count each day.
queue<triple> que;									// queue helps it is possible to read in bfs search.
vector<triple> rippen;								// It saves the result of coordinate in Search function.

void Search(int ***arr, int M, int N, int H, int value)		// Search the coordinate if value exists.
{
	for (int i = 0; i < H; i++)
		for (int j = 0; j < N; j++)
			for (int k = 0; k < M; k++)
				if (arr[i][j][k] == value)
					rippen.push_back(triple(i, j, k));
}

void BFS(int ***arr, int M, int N, int H)
{
	int term, count = 0;				// term = It saves the size of queue after checking adjacent node exists or not in each step.
										// It is for counting day. [while문이 queue.empty조건으로 돌아가기 때문에, 날짜를 counting하기 위한 조건이 필요.]

	// At first time, push the origin coordinate of rippen tomato.
	for (int i = 0; i<rippen.size(); i++)
		que.push(triple(get<0>(rippen[i]), get<1>(rippen[i]), get<2>(rippen[i])));
	
	// Another way to access tuple variable with iterator.
	/*
	for (vector<tuple<int, int, int>>::const_iterator i = rippen.begin(); i != rippen.end(); ++i)
		que.push(triple(get<0>(*i), get<1>(*i), get<2>(*i)));
	*/
	
	term = que.size();				//[term==count라는 것이, 한 step(level)이 search되었다고 볼 수 있다.]
	while (!que.empty())
	{
		if (term == count)			// It represents each step of bfs search.
		{
			Day++;
			count = 0;
			term = que.size();
		}

		int x = get<0>(que.front());		// x = Height.
		int y = get<1>(que.front());		// y = column.
		int z = get<2>(que.front());		// z = width.

		// Check adjacent node exists or not.
		if (z - 1 >= 0 && arr[x][y][z-1] == 0)					// left
		{
			arr[x][y][z-1] = 1;
			que.push(triple(x, y, z - 1));
		}

		if (z + 1 <= M - 1 && arr[x][y][z+1] == 0)				// right
		{
			arr[x][y][z+1] = 1;
			que.push(triple(x, y, z + 1));
		}

		if (y - 1 >= 0 && arr[x][y-1][z] == 0)					// up
		{
			arr[x][y-1][z] = 1;
			que.push(triple(x, y - 1, z));
		}
		
		if (y + 1 <= N - 1 && arr[x][y+1][z] == 0)			// down
		{
			arr[x][y+1][z] = 1;
			que.push(triple(x, y + 1, z));
		}

		if (x - 1 >= 0 && arr[x-1][y][z] == 0)					// front
		{
			arr[x-1][y][z] = 1;
			que.push(triple(x - 1, y, z));
		}

		if (x+1 <= H-1 && arr[x+1][y][z] == 0)					// back
		{
			arr[x+1][y][z] = 1;
			que.push(triple(x + 1, y, z));
		}

		que.pop();		// Checking adjacent node is finished above, it should be popped. 
		count++;			// If there is nothing to fit above conditions, it should be popped as well.
	}
	rippen.clear();		// It is for using Search function again.
}

int main(void)
{
	std::ios_base::sync_with_stdio(false);

	int M, N, H;								// M = width.	N = column.		H = height.
	cin >> M >> N >> H;

	int ***input = new int **[H];		// Allocate three-dimension array dynamically.
	for (int i = 0; i < H; i++)
	{
		input[i] = new int*[N];
		for (int j = 0; j < N; j++)
		{
			input[i][j] = new int[M];
			for (int k = 0; k < M; k++)
				cin >> input[i][j][k];
		}
	}

	// check three dimension array
	/*
	for (int i = 0; i < H; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cout << "\n";
			for (int k = 0; k < M; k++)
				cout << input[i][j][k] << " ";
		}
	}
	*/
	

	Search(input, M, N, H, 1);			// Search the coordinate of rippen tomato.(value = 1)

	BFS(input, M, N, H);					// Do bfs searching.

	Search(input, M, N, H, 0);			// Search the coordinate of unrippen tomato.(value = 0)
									// Is there any unrippen tomato, doing bfs search is impossible.
	if (rippen.empty())					// The result of coordinate is stored in rippen vector.
		cout << Day << "\n";			// Judging with rippen vector.
	else
		cout << -1 << "\n";
}