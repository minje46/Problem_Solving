#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>

#define MAX 32001							// Set max number.

using namespace std;

vector<int> graph[MAX];					// The memory of graph.
int indegree[MAX];							// The memory of indgree to check.

void BFS(int N)								// To figure out the breadth first search.
{
	queue<int>que;							// The memory of queue to control BFS.
	for (int i = 1; i <= N; i++)
		if (!indegree[i])						// If the indegree is zero, it should be pushed in queue.
			que.push(i);						// [������ 0�� ��츸 queue�� push.]					
	
	while (!que.empty())
	{
		auto idx = que.front();				// The first node in queue will be used as visited edge.
		que.pop();								// [Queue�� �ִ� ù ��° node�� �湮�Ǵ� edge�� ���.]

		cout << idx << endl;
		for (int i = 0; i < graph[idx].size(); i++)	// To search all siblings or children from this edge.
		{											// [�湮�� edge���� connected�� ��� node�� search�ϱ� ����.]	
			indegree[graph[idx][i]]--;				// The visited edge will be deleted.
			if (!indegree[graph[idx][i]])				// [�湮�� node�� ���ŵǾ��ٰ� �����, connected�� indegree�� ������ decrease.]
				que.push(graph[idx][i]);				// [Indegree�� 0�� �� node�� �ִ� ���, queue�� ���Ӱ� push.]
		}
	}
}

int main(void)
{
	int N, M;										// N = The number of edges.		M = The number of vertexes.
	cin >> N >> M;
	for (int i = 0; i < M; i++)
	{
		int A, B;
		cin >> A >> B;
		graph[A].push_back(B);
		indegree[B]++;						// If the edge is connected each other, the indegree of edge should be increased.	
	}

	BFS(N);										// To figure out topological sort using BFS.
}