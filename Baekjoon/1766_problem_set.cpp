#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>

#define MAX 32001					// Set max number.

using namespace std;

int N, M;									// N = The number of questions.		M = The number of data about questions.
vector<int>graph[MAX];			// The memory of graph.
int indegree[MAX];					// The memory of indgree to check.
queue<int>result;					// The memory of results.

void Topological()					// To figure out the topological sort.
{
	priority_queue<int, vector<int>, greater<int>>que;	// The memory of priority queue to control BFS.

	for (int i = 1; i <= N; i++)
		if (!indegree[i])				// If the indegree is zero, it should be pushed in queue.
			que.push(i);				// [차수가 0인 경우만 queue에 push.]		

	while (!que.empty())
	{
		auto idx = que.top();		// The first node in queue will be used as visited edge.
		que.pop();						// [Queue에 있는 첫 번째 node가 방문되는 edge로 사용.]
		result.push(idx);				// To show the order at last.

		for (int i = 0; i < graph[idx].size(); i++)		// To search all siblings or children from this edge.
		{															// [방문한 edge에서 connected된 모든 node를 search하기 위함.]	
			indegree[graph[idx][i]]--;					// The visited edge will be deleted.
			if (!indegree[graph[idx][i]])					// [방문한 node는 제거되었다고 여기고, connected된 indegree의 차수를 decrease.]
				que.push(graph[idx][i]);					// [Indegree가 0이 된 node가 있는 경우, queue에 새롭게 push.]
		}
	}
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin >> N >> M;
	for (int i = 0; i < M; i++)
	{
		int a, b;
		cin >> a >> b;
		graph[a].push_back(b);
		indegree[b]++;				// If the edge is connected each other, the indegree of edge should be increased.	
	}

	Topological();						// To figure out topological sort using BFS.

	while(!result.empty())			// Output.
	{
		cout << result.front() << " ";
		result.pop();
	}
	cout << endl;
}