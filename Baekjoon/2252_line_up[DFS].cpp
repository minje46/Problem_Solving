#include<iostream>
#include<algorithm>
#include<vector>
#include<stack>

#define MAX 32001					// Set max number.

using namespace std;

vector<int> graph[MAX];			// The memory of graph.
int visit[MAX];							// The memory of visited or not.
stack<int> stk;						// The memory of stack for DFS.

void DFS(int node)					// To figure out the depth first search.
{
	visit[node] = true;				// When the node was used as input, it should be treated as visited.
	for (int i = 0; i < graph[node].size(); i++)	// To search all siblings or children from this edge.
	{										// [방문한 edge에서 connected된 모든 node를 search하기 위함.]	
		if (!visit[graph[node][i]])						// To search edge which is not visited yet.
			DFS(graph[node][i]);						// Do recursive search.
	}
	stk.push(node);					// The result which was visited now is put in stack.
}

int main(void)						
{
	int N, M;								// N = The number of edges.		M = The number of vertexes.
	cin >> N >> M;
	for (int i = 0; i < M; i++)
	{
		int A, B;
		cin >> A >> B;				
		graph[A].push_back(B);	
	}
	
	for (int i = 1; i <= N; i++)
		if (!visit[i])						// To figure out topological sort using DFS.
			DFS(i);						// [DFS를 이용하기 위해 edge의 방문 여부를 확인.]

	while (!stk.empty())				// Stack is the memory of topological sorted results.
	{
		cout << stk.top() << endl;
		stk.pop();
	}
}