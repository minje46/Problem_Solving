#include <iostream>
#include <vector>
#include <queue>

# define INF 987654321				// Initialize INFINITY.

using namespace std;

struct Edge									// Memory structure of edge. 			
{
	int to;									// Where this edge is heading to.
	int cost;									// path's cost.
	Edge(int to, int cost) : to(to), cost(cost) { }	// Bit field.
};

vector<Edge> edge[20001];		// Memory of edge.
int dist[20001];							// Memory of distance.
bool visit[20001];					// Memory of visited or not.		

void Dijkstra(int V, int E, int start)	// Figure all edge's shortest path from start point.
{
	for (int i = 1; i <= V; i++)			// Initailize edge's distance as INFINITY.
		dist[i] = INF;						// [시작 노드에서 모든 노드로 향하는 길은 INF로 초기화 하고 시작한다.]

	dist[start] = 0;						// Start edge is alwyas zero. 
												//[자신의 노드로 되돌아오는 길은 없다고 가정했기 때문에, 시작 노드의 path는 0으로 고정할 수 있다.]
	priority_queue<pair<int, int>> que;		
	que.push(make_pair(0, start));	// Push the start point with cost 0. [cost 0인 채로 start node를 priority queue에 push한다.]

	while (!que.empty())				// Till there is no more node in queue.
	{
		auto idx = que.top();			// auto makes select data type automatically.
		que.pop();							// [Queue의 node를 pop하고 해당 edge의 connection 여부를 확인한다.]
		int x = idx.second;				// [Pop 한 edge의 번호(index)를 저장한다.]
		if (visit[x])						// [이미 방문한 edge일 경우, pass 한다.]
			continue;						// [이미 방문한 edge의 경우, 이미 shortest path로 저장이 되었을 것이다.]
												// [Dijkstra algorithm의 정당성으로 증명이 가능하다.]
		visit[x] = true;					// [A->B로 가는 path보다 A->C->B로 경유하는 path보다 not short할 경우,
												// Priority queue에서 B가 아닌, C가 top을 유지했어야 한다.]
		for (int i = 0; i<edge[x].size(); i++)		// [해당 edge에 연결된 간선의 개수 만큼 loop로 확인한다.]
		{
			int y = edge[x][i].to;						// [해당 edge에서 도착지로 향하는 edge의 위치 저장.]
			if (dist[y] > dist[x] + edge[x][i].cost)	// [도착점 edge에서 저장하고 있는 path와 출발지에서 도착지까지의 path의 합과 비교해서 shortest를 pick.]
			{
				dist[y] = dist[x] + edge[x][i].cost;
				que.push(make_pair(-dist[y], y));		// [first node는 distance 계산에서는 필요 없지만, 
			}														// Priority queue의 자동 sorting에 맞춰 올바른 우선순위를 가지기 위해서 필요하다.]	
		}
	}
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	
	int V, E, start;									// V = The number of vertex.		E = The number of line.			start = The start point.
	cin >> V >> E;								// Input of vertex and line.
	cin >> start;									// Input of start point.
	
	for (int i = 0; i<E; i++)
	{
		int x, y, z;									// Temporary variables to store start node, end node, cost.		
		cin >> x >> y >> z;						// Input of start, end, cost.
		edge[x].push_back(Edge(y, z));	// Store the each edge's vertex and cost in structure.	
	}

	Dijkstra(V, E, start);							// Figure out shortest path individually.

	for (int i = 1; i <= V; i++)					// All vertexs.
	{
		if (dist[i] >= INF)							// There is no connection between edges.	
			cout << "INF" << endl;				// Edges are initialized as INFIITY.	
		else
			cout << dist[i] << endl;			// Out put of edge's shortest path.
	}
}