#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
#include<cstring>

using namespace std;

vector<int> vertex[1001];
bool visited[1001];
vector<int> result;												// Result storage.

void DFS(int value)												// Get the vertex. [������ �Է¹޴´�.]
{
	visited[value] = true;										// Check whether the vertex was visited or not. [������ �湮 ���� check.]
	result.push_back(value);									// For the result sotrage.

	for (int i = 0; i < vertex[value].size(); i++)			// Check the linked list from the current vertex.
	{																	// [���� �������� ����� list���� ���ʴ�� Ȯ��.]					
		int next = vertex[value][i];							// Find the next linked vertex from current vertex.
																		// [���� �������� ������ ������ ������ ã�´�.]
		if (visited[next] == false)								// Check wherther the vertex was visited before or not.
			DFS(next);												// [ã�� ������ �湮 ���θ� Ȯ���Ѵ�.]		
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
	{																	//	[ť�� ���� ������ ������ �湮�ؾ� �Ѵٴ� ���� �ǹ�.]
		int node = que.front();									// Visit the first vertex for the BFS order. [BFS ������ ���� front���� ���� �湮]
		que.pop();													// After visited, it should be popped. [�湮 �ߴٰ� ����� pop.]
		result.push_back(node);

		for (int i = 0; i < vertex[value].size(); i++)			// Check the linked list from the current vertex.
		{																	// [���� �������� ����� list���� ���ʴ�� Ȯ��.]
			int next = vertex[value][i];							// Find the next linked vertex from current vertex.
																			// [���� �������� ������ ������ ������ ã�´�.]
			if (visited[next] == false)								// Check wherther the vertex was visited before or not.
			{																// [ã�� ������ �湮 ���θ� Ȯ���Ѵ�.]		
				visited[next] = true;
				que.push(next);										// The next vertex which should be visited is kept in queue.	
			}																// [������ �湮�ؾ� �� ������ ť���� ����ȴ�.]
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
	}														// �� ������ ������ �����ٸ�, linked list ó�� chaining ������ ����.

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