#include<iostream>
#include<algorithm>
#include<queue>
#include<cstring>
#include<vector>

using namespace std;

const int MAX = 300;												// The maximum size of chess board.
const int INF = 987654321;										// The max number to initialize.	

typedef struct  Coordinate										// That's because the data input is coordinate. 
{
	int x;
	int y;
}cor;

int dx[] = { -1, -2, -2, -1, 1, 2, 1, 2 };					// The 'x' points knights can move.
int dy[] = { -2, -1, 1, 2, -2, -1, 2, 1 };					// The 'y' points knights can move.
bool visited[MAX][MAX];											// The bucket to store whether this coordinate was visited or not.	
int cache[MAX][MAX];											// The bucket to store the count of this coordinate.
																			// [Count�� ����ϱ� ���� ��ü �������� �޸𸮸� �Ҵ��ؾߵɱ�...?]
void Initialize()															// Do initialize the chache bucket.
{
	for (int i = 0; i < MAX; i++)
		for (int j = 0; j < MAX; j++)
			cache[i][j] = INF;
}

int BFS(int len,  int str_x, int str_y, int dst_x, int dst_y)
{
	queue<pair<int, int>> que;

	que.push(make_pair(str_x, str_y));														// Push the start point in queue.
	while (!que.empty())																		// The queue is not empty means there is more points should move.
	{																									// [ť�� knights�� �̵��ؾ� �� ��ǥ�� ������ ����Ǿ� �ִ�.]		
		pair<int, int> current = que.front();													// The first one of queue is the same order of bfs.
		que.pop();																					// [ť�� ù��° ������ Ž���ϴ� ���� bfs Ž�� ������ �����ϰ� �Ǿ� �ִ�.]	
		cache[str_x][str_y] = 0;

		if (current.first == dst_x && current.second == dst_y)						// Check the destination or not.
			return cache[current.first][current.second];								// If the destination is correct, it returns the count how many times it takes from start point.

		for (int i = 0; i < 8; i++)
		 {
			cor next = { current.first + dx[i], current.second+dy[i]};				// The next movement of knights.
																										// [Knight�� ������ �� �ִ� ������ �̸� �����س��� array�� ���.]		
			if (0 <= next.y&&next.y < len && 0 <= next.x&&next.x < len)			// Check the next movement is wrong or not.
			{																							// [Knight�� ���� ��ġ�� �߸��� ��ġ(ü�� �� �ʰ�)�� �ƴ��� üũ.]	
				if (!visited[next.x][next.y])													// Check the next movement was visited before.
				{																						// [Kinght�� ���� ��ġ�� �̹� �湮 �Ǿ����� üũ.]
					que.push(make_pair(next.x, next.y));									// Push the next movement in queue means it is the coordinate should visit later,
					visited[next.x][next.y] = true;											// And check the visited in advance.
					cache[next.x][next.y] = min(cache[next.x][next.y], cache[current.first][current.second] + 1);
				}// [���� ��ġ���� �̵��� �� �ִ� ��� ��带 Ȯ���ϰ�, ť�� �����ϴ� ����... ���� ����� ���� ������ �����̶�� ���� �ǹ��ϱ� ������ +1�� level�� üũ���ش�.]		
			}
		}
	}

}

int main(void)
{
	int T;																			// T = Test case.
	vector<int> result;
	cin >> T;

	for (int i = 0; i < T; i++)
	{
		int len;																	// len = Size of chess board.
		cor start, end;															// start, end = Coordinate of start and end point.

		memset(visited, false, sizeof(visited));						// Initialize the visited bucket.
		Initialize();																// Initialize the cache bucket.	

		cin >> len;	
		cin >> start.x >> start.y;
		cin >> end.x >> end.y;

		 result.push_back(BFS(len, start.x, start.y, end.x, end.y));
	}

	for (int i = 0; i < result.size(); i++)								
		cout << result[i] << endl;											// All results are stored in vector.	
}