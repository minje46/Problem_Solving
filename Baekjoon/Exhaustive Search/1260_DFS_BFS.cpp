#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
#include<cstring>

using namespace std;

vector<int> vertex[1001];
bool visited[1001];
vector<int> result;												// Result storage.

void DFS(int value)												// Get the vertex. [정점을 입력받는다.]
{
	visited[value] = true;										// Check whether the vertex was visited or not. [정점의 방문 여부 check.]
	result.push_back(value);									// For the result sotrage.

	for (int i = 0; i < vertex[value].size(); i++)			// Check the linked list from the current vertex.
	{																	// [현재 정점에서 연결된 list들을 차례대로 확인.]					
		int next = vertex[value][i];							// Find the next linked vertex from current vertex.
																		// [현재 정점에서 간선을 가지는 정점을 찾는다.]
		if (visited[next] == false)								// Check wherther the vertex was visited before or not.
			DFS(next);												// [찾은 정점의 방문 여부를 확인한다.]		
	}
}

void BFS(int value)
{
	queue<int> que;

	memset(visited, false, sizeof(visited));				// Reset the visited memory to reuse.
	result.clear();													// Reset the result memory to reuse.								

	visited[value] = true;										// Check the vertex is visiting now.
	que.push(value);												// At frist, push the start vertex in queue.

	while (!que.empty())										// Queue means there is any vertex should visit.
	{																	//	[큐에 값이 있으면 정점을 방문해야 한다는 것을 의미.]
		int node = que.front();									// Visit the first vertex for the BFS order. [BFS 순서에 따라 front에서 부터 방문]
		que.pop();													// After visited, it should be popped. [방문 했다고 여기고 pop.]
		result.push_back(node);

		for (int i = 0; i < vertex[value].size(); i++)			// Check the linked list from the current vertex.
		{																	// [현재 정점에서 연결된 list들을 차례대로 확인.]
			int next = vertex[value][i];							// Find the next linked vertex from current vertex.
																			// [현재 정점에서 간선을 가지는 정점을 찾는다.]
			if (visited[next] == false)								// Check wherther the vertex was visited before or not.
			{																// [찾은 정점의 방문 여부를 확인한다.]		
				visited[next] = true;
				que.push(next);										// The next vertex which should be visited is kept in queue.	
			}																// [다음에 방문해야 할 정점은 큐에서 저장된다.]
		}
	}
}

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	int N, M, start;
	cin >> N >> M >> start;						// N = The number of vertex.			M = The number of branch.			start = The start point(vertex).
	
	for (int i = 0; i < M; i++)
	{
		int x, y;											// Input of vertex connection. 
		cin >> x >> y;												

		vertex[x].push_back(y);					// Using an adjacent list which is implemented by vector.
		vertex[y].push_back(x);					// Chaining the node on each vertex which has branch.
	}														// 각 정점이 간선을 가진다면, linked list 처럼 chaining 구조로 연결.

	for (int i = 1; i <= N; i++)
		sort(vertex[i].begin(), vertex[i].end());		// The vertex starts from 1 not 0.

	DFS(start);

	for (int i = 0; i < result.size(); i++)
		cout << result[i] << " ";
	cout << endl;

	BFS(start);

	for (int i = 0; i < result.size(); i++)
		cout << result[i] << " ";
	cout << endl;

}