#include<iostream>
#include<algorithm>
#include<vector>

#define INF 987654321				// Initialize INFINITY.

using namespace std;

vector<pair<int, int>> edge[10001];		// Memory of edge.
int dist[10001];							// Memory of distance.
bool visited[10001];					// Memory of visited or not.	
int answer = 0;							// Minimum cost of spanning tree.

void Prim(int V, int E)					// Figure out minimum spanning tree.
{
	for (int i = 1; i <= V; i++)			// Initailize edge's distance as INFINITY.
		dist[i] = INF;						// [시작 노드에서 모든 노드로 향하는 길은 INF로 초기화 하고 시작한다.]

	dist[1] = 0;							// Start edge is alwyas zero. 
												//[자신의 노드로 되돌아오는 길은 없다고 가정했기 때문에, 시작 노드의 path는 0으로 고정할 수 있다.]
	for (int i = 1; i <= V; i++)			// Loop for departure's vertex. [시작 점의 loop.]
	{
		int idx = -1, min_dist = INF;	// idx = index of smallest node.			min_dist = minimum distance from departure to destination vertex.
		for (int j = 1; j <= V; j++)		// Loop for destination's vertex. [도착 점의 loop.]
		{										//[시작 점에서 갈 수 있는 모든 vertex들을 한개씩 보겠다는 것.]
			if (!visited[j] && min_dist > dist[j])	// Condition for selecting proper vertex.			
			{									// [인접한 node들 중에서 가장 작은 cost의 node를 선택하기 위함. (+ 방문하지 않은 node들 중에서)]
				min_dist = dist[j];		// Update minimum distance to compare again in next loop.
				idx = j;						// [node의 번호(index)를 저장하고 있는 것.]
			}
		}

		answer += min_dist;				// For total distance of MST.
		visited[idx] = true;				// Update the node was visited.
		for (auto e : edge[idx])		// [선택된 node에서 이동할 수 있는 node로의 shortest path를 update.]
			dist[e.first] = min(dist[e.first], e.second);	// [vertex가 기존에 저장하고 있던 minimum path와 selected departure vertex에서 destination까지의 path 중에서 minimum path cost를 비교한다.]
	}											// [e.first가 destination의 index를 뜻한다.]		[e.second는 path의 cost를 뜻한다.]
}
	
int main(void)
{
	ios_base::sync_with_stdio(false);

	int V, E;											// V = The number of vertex.		E = The number of line.
	cin >> V >> E;						
	for (int i = 0; i < E; i++)
	{
		int x, y, z;									// Temporary variables to store start node, end node, cost.		
		cin >> x >> y >> z;						// Input of start, end, cost.
		edge[x].push_back({ y, z });		// Build adjacent array.
		edge[y].push_back({ x, z });		// Bi-directed graph.
	}
	
	Prim(V, E);										// Figure out minimum spanning tree.	

	cout << answer << endl;					// Out put of minimum spanning tree.
}