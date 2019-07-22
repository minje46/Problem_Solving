#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

#define INF 987654321						// Initialize INFINITY.
#define MAX 502									// Initialize MAX.

using namespace std;

vector<pair<int, int>> edge[MAX];		// Memory of edge.
vector<int> hist[MAX];							// Memory of previous edge's.
bool visited[MAX];								// Memory of visited or not.
int dist[MAX];										// Memory of distance.

int Dijkstra(int N, int start, int end)			// To figure out how the network will be restored.
{
	for (int i = 0; i < N; i++)					// Initialize memory.
	{
		dist[i] = INF;								// Set each distance as INFINITY.
		visited[i] = false;							// Set each edge's visited as false.
	}
	dist[start] = 0;								// Start edge is alwyas zero. 
													//[자신의 노드로 되돌아오는 길은 없다고 가정했기 때문에, 시작 노드의 path는 0으로 고정할 수 있다.]
	priority_queue<pair<int, int>> que;		// Push the start point with cost 0. [cost 0인 채로 start node를 priority queue에 push한다.]
	que.push(make_pair(0, start));
	while (!que.empty())						// Till there is no more node in queue.
	{
		auto idx = que.top();					// auto sets data type automatically.
		que.pop();
		int dpt = idx.second;

		if (visited[dpt])							// [이미 방문한 edge일 경우, pass 한다. 이미 방문한 edge의 경우, 이미 shortest path로 저장이 되었을 것이다.]
			continue;								// [Dijkstra algorithm의 정당성으로 증명이 가능하다.]
		visited[dpt] = true;						// [A->B로 가는 path보다 A->C->B로 경유하는 path보다 not short할 경우, Priority queue에서 B가 아닌, C가 top을 유지했어야 한다.]

		for (int i = 0; i < edge[dpt].size(); i++)	// [해당 edge에 연결된 간선의 개수 만큼 loop로 확인한다.]
		{
			int dst = edge[dpt][i].first;				// [해당 edge에서 도착지로 향하는 node의 번호 저장.]
			if (dist[dst] > dist[dpt] + edge[dpt][i].second && edge[dpt][i].second != -1)		// [cost = -1인 경우는, delete된 간선을 의미.]
			{													// [도착점 edge에서 저장하고 있는 path와 출발지에서 도착지까지의 path의 합과 비교해서 shortest를 pick.]
				dist[dst] = dist[dpt] + edge[dpt][i].second;	// Update shortest path.
				que.push(make_pair(-dist[dst], dst));

				hist[dst].clear();							// [기존에 hist에 저장되어 있는 edge가 있더라도, 최단 경로가 update되었기 때문에 초기화가 필요.]	
				hist[dst].push_back(dpt);				// [Destination으로 오는 path의 previous edge와 cost를 hist에 저장.]
			}
			// If there is another shortest path which has same cost. [최단 경로가 여러개 있을 경우.]
			else if (dist[dst] == dist[dpt] + edge[dpt][i].second && edge[dpt][i].second != -1)
				hist[dst].push_back(dpt);			// [Destination으로 오는 모든 shortest path를 저장하고 있어야 BFS로 탐색이 가능하다.]
		}
	}
	if (dist[end] == INF)		// It means there is no path to get destination.
		return -1;

	else
		return dist[end];			// Return the shortest path.
}

void BFS(int end)				// To figure out what is the previous edge from destination edge using BFS search.
{
	queue<int> que;				// [BFS 탐색을 위해 접근 가능한 모든 node(edge)를 queue로 관리한다.]
	que.push(end);
	while (!que.empty())		// Till there is no more node in queue.
	{									// [Destination으로 도달하는 path를 거꾸로 되짚어가는 방식이다.]
		int dpt = que.front();	// [그래서, destination(end)가 departure edge로 설정이 된다.]
		que.pop();

		for (int i = 0; i < hist[dpt].size(); i++)		// [Destination으로 도달할 수 있는 모든 edge를 search해야한다.]
		{											// vector<pair<int, int>>hist = <previous edge, cost> 를 저장.
			int dst = hist[dpt][i];			// [previous edge가 destination으로 set해서 거꾸로 찾아가는 것.]

			for (int i = 0; i < edge[dst].size(); i++)	// [destination edge로 설정된 edge에서 접근 가능한 모든 path를 search하기 위함.]
				if (edge[dst][i].first == dpt)				// [edge[dst][i].first 는 previous edge에서 destination으로 갈 수 있는 edge를 뜻함.]
					edge[dst][i].second = -1;			// [Shortest path가 되는 edge를 찾았다면, 해당 path를 delete하기 위해 -1로 설정.]
														// [Dijkstra algorithm은 음수 cost를 고려하지 않기 때문에, -1로 간선을 지웠다고 여길 수 있다.]
			que.push(dst);					// [Previous edge 또한 어떤 edge를 거쳐서 왔을 수 있기 때문에, BFS 탐색이 필요.]
		}
	}
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	int N, M;

	while (true)
	{
		cin >> N >> M;					// Input of the number of edges and connections.
		if (N == 0 && M == 0)			// Exit condition.
			break;

		for (int i = 0; i < MAX; i++)	// Initialize again for each test case.
			edge[i].clear();				// Clear the edge memory.
		memset(hist, 0, sizeof(hist));		// Clear previous edge's memory.

		int start, end;
		cin >> start >> end;				// Input of start and end point.
		for (int i = 0; i < M; i++)
		{
			int u, v, p;
			cin >> u >> v >> p;
			edge[u].push_back(make_pair(v, p));
		}

		Dijkstra(N, start, end);			// To set shortest path on graph. [Graph에 shortest path를 set하기 위해, dijkstra algorithm이 사용된다.]

		BFS(end);							// To rebuild graph without shortest path. [최단 경로를 지운 graph로 update가 필요하기에 BFS를 사용한다.]

		cout << Dijkstra(N, start, end) << endl;		// Output of almost shortest path.
	}
}
