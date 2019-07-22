#include<iostream>
#include<algorithm>
#include<vector>
#include<memory.h>

#define MAX 20001

using namespace std;

int V, E;				// V = The number of vertex.			E = The number of edges.
vector<int> graph[MAX];		// The memory of graph.
int visit[MAX];		// The memory of whether visited or not.

bool Bipartite()	// To figure out that it is bipartite graph or not.	
{
	for (int i = 1; i <= V; i++)		// From each vertex.
	{	
		for (int j = 0; j < graph[i].size(); j++)		// To all adjacent vertexes.
		{
			if (visit[i] == visit[graph[i][j]])			// Do check these nodes are having same color or not.
				return false;			// Not bipartite graph.
		}
	}
	return true;		// Bipatite graph.			
}

void DFS(int node, int color)		// To set each different color from current node.
{						// [현재 node에서 adjacent node들이 서로 다른 color를 가지도록 visit에 color(value)를 set.]
	visit[node] = color;
	for (int i = 0; i < graph[node].size(); i++)
	{
		if (!visit[graph[node][i]])		// If there is no color yet.
			DFS(graph[node][i], 3 - color);		// Check adjacent node from current node.
	}															// [현재 node에서 인접한 node들을 dfs로 check.]	
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	int T;				// T = The number of test case.
	cin >> T;
	while (T--)
	{	
		// Initialization.
		for (int i = 0; i < MAX; i++)
			graph[i].clear();
		fill(visit, visit + MAX, 0);

		cin >> V >> E;
		for (int i = 0; i < E; i++)		// Organize graph.
		{
			int a, b;
			cin >> a >> b;
			graph[a].push_back(b);
			graph[b].push_back(a);
		}

		for (int i = 1; i <= V; i++)	
			if (visit[i] == 0)
				DFS(i, 1);					// To set each different color from current node.
		
		if (Bipartite())						// To figure out that it is bipartite graph or not.	
			cout << "YES" << endl;
		else
			cout << "NO" << endl;
	}
}