#include<iostream>
#include<vector>
#include<queue>

#define INF 987654321					// Initialize INFINITY.

using namespace std;

vector<pair<int, int>> restoration;		// Memory of vertex history.
vector<pair<int, int>> edge[1001];	// Memory of edge.
bool visited[1001];							// Memory of visited or not.	
int dist[1001];								// Memory of distance.

void Dijkstra(int N, int M)					// To figure out how the network will be restored.
{
	int prev = -1;								// Memory of start point's index. [시작점의 index를 저장하기 위함.]	

	for (int i = 1; i <= N; i++)				// Initailize edge's distance as INFINITY.
		dist[i] = INF;							// [시작 노드에서 모든 노드로 향하는 길은 INF로 초기화 하고 시작한다.]
	dist[1] = 0;								// Start edge is alwyas zero. 
													//[자신의 노드로 되돌아오는 길은 없다고 가정했기 때문에, 시작 노드의 path는 0으로 고정할 수 있다.]
	priority_queue<pair<int, int>> que;	// Push the start point with cost 0. [cost 0인 채로 start node를 priority queue에 push한다.]
	que.push(make_pair(0, 1));			// Pair<distance, destination> 을 뜻함.
	while (!que.empty())					// Till there is no more node in queue.
	{
		auto idx = que.top();				// auto makes select data type automatically.
		que.pop();								// [Queue의 node를 pop하고 해당 edge의 connection 여부를 확인한다.]

		if (visited[idx.second])				// [이미 방문한 edge일 경우, pass 한다. 이미 방문한 edge의 경우, 이미 shortest path로 저장이 되었을 것이다.]
			continue;							// [Dijkstra algorithm의 정당성으로 증명이 가능하다.]
		visited[idx.second] = true;		// [A->B로 가는 path보다 A->C->B로 경유하는 path보다 not short할 경우, Priority queue에서 B가 아닌, C가 top을 유지했어야 한다.]
		
		for (int i = 0; i < edge[idx.second].size(); i++)	// [해당 edge에 연결된 간선의 개수 만큼 loop로 확인한다.]
		{
			int y = edge[idx.second][i].first;					// [해당 edge에서 도착지로 향하는 node의 번호 저장.]
			if (dist[y] > dist[idx.second] + edge[idx.second][i].second)
			{										// [도착점 edge에서 저장하고 있는 path와 출발지에서 도착지까지의 path의 합과 비교해서 shortest를 pick.]
				dist[y] = dist[idx.second] + edge[idx.second][i].second;
				que.push(make_pair(-dist[y], y));				// [first node는 distance 계산에서는 필요 없지만, Priority queue의 자동 sorting에 맞춰 올바른 우선순위를 가지기 위해서 필요하다.]	
				
				for (int i = 0; i < restoration.size(); i++)		// Searching the restoration's memory.
				{															// [Path(간선)의 정보를 저장하고 있는 restoration을 search.]		
					if (restoration[i].second == y)				// Search the path already exists or not.
					{														// [도착지로 도달하기 위한 경로가 이미 존재하지만,
						prev = i;											// 더 짧은 경로를 발견했기 때문에 update가 필요하다.]
						break;											// [이를 위한, index를 저장.]			
					}
					else													// Not exist.
						prev = -1;
				}

				if (prev == -1)											// There is no path to get destination, just store the path.
					restoration.push_back(make_pair(idx.second, y));	// [도착지로 도달하기 위한 path가 없기 때문에 경로 기록을 위해 저장.]
				else														// There is already path of destination.	
					restoration[prev].first = idx.second;		// [Update가 필요한 경우.]
			}
		}
	}
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	int N, M;
	cin >> N >> M;						// Input of the number of edges and connections.

	for (int i = 0; i < M; i++)
	{
		int a, b, c;							// Temporary variable.
		cin >> a >> b >> c;				// Input of start, end, cost.
		edge[a].push_back(make_pair(b, c));	// Build adjacent list.
		edge[b].push_back(make_pair(a, c));	// Bi-directed graph.	
	}

	Dijkstra(N, M);						// Figure out the method of network resotration.

	cout << restoration.size() << endl;		// Output of the number of MST nodes.
	for (int i = 0; i < restoration.size(); i++)		// Output of each path from start to end.
		cout << restoration[i].first << " " << restoration[i].second << endl;
}