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
																			// [Count를 계산하기 위해 전체 사이즈의 메모리를 할당해야될까...?]
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
	{																									// [큐에 knights가 이동해야 할 좌표의 정보가 저장되어 있다.]		
		pair<int, int> current = que.front();													// The first one of queue is the same order of bfs.
		que.pop();																					// [큐의 첫번째 노드부터 탐색하는 것은 bfs 탐색 순서와 동일하게 되어 있다.]	
		cache[str_x][str_y] = 0;

		if (current.first == dst_x && current.second == dst_y)						// Check the destination or not.
			return cache[current.first][current.second];								// If the destination is correct, it returns the count how many times it takes from start point.

		for (int i = 0; i < 8; i++)
		 {
			cor next = { current.first + dx[i], current.second+dy[i]};				// The next movement of knights.
																										// [Knight가 움직일 수 있는 방향을 미리 설정해놓은 array로 계산.]		
			if (0 <= next.y&&next.y < len && 0 <= next.x&&next.x < len)			// Check the next movement is wrong or not.
			{																							// [Knight의 다음 위치가 잘못된 위치(체스 판 초과)가 아닌지 체크.]	
				if (!visited[next.x][next.y])													// Check the next movement was visited before.
				{																						// [Kinght의 다음 위치가 이미 방문 되었는지 체크.]
					que.push(make_pair(next.x, next.y));									// Push the next movement in queue means it is the coordinate should visit later,
					visited[next.x][next.y] = true;											// And check the visited in advance.
					cache[next.x][next.y] = min(cache[next.x][next.y], cache[current.first][current.second] + 1);
				}// [현재 위치에서 이동할 수 있는 모든 노드를 확인하고, 큐에 저장하는 것은... 현재 노드의 다음 레벨의 노드들이라는 것을 의미하기 때문에 +1로 level을 체크해준다.]		
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