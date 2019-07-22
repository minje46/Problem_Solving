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
		dist[i] = INF;						// [���� ��忡�� ��� ���� ���ϴ� ���� INF�� �ʱ�ȭ �ϰ� �����Ѵ�.]

	dist[1] = 0;							// Start edge is alwyas zero. 
												//[�ڽ��� ���� �ǵ��ƿ��� ���� ���ٰ� �����߱� ������, ���� ����� path�� 0���� ������ �� �ִ�.]
	for (int i = 1; i <= V; i++)			// Loop for departure's vertex. [���� ���� loop.]
	{
		int idx = -1, min_dist = INF;	// idx = index of smallest node.			min_dist = minimum distance from departure to destination vertex.
		for (int j = 1; j <= V; j++)		// Loop for destination's vertex. [���� ���� loop.]
		{										//[���� ������ �� �� �ִ� ��� vertex���� �Ѱ��� ���ڴٴ� ��.]
			if (!visited[j] && min_dist > dist[j])	// Condition for selecting proper vertex.			
			{									// [������ node�� �߿��� ���� ���� cost�� node�� �����ϱ� ����. (+ �湮���� ���� node�� �߿���)]
				min_dist = dist[j];		// Update minimum distance to compare again in next loop.
				idx = j;						// [node�� ��ȣ(index)�� �����ϰ� �ִ� ��.]
			}
		}

		answer += min_dist;				// For total distance of MST.
		visited[idx] = true;				// Update the node was visited.
		for (auto e : edge[idx])		// [���õ� node���� �̵��� �� �ִ� node���� shortest path�� update.]
			dist[e.first] = min(dist[e.first], e.second);	// [vertex�� ������ �����ϰ� �ִ� minimum path�� selected departure vertex���� destination������ path �߿��� minimum path cost�� ���Ѵ�.]
	}											// [e.first�� destination�� index�� ���Ѵ�.]		[e.second�� path�� cost�� ���Ѵ�.]
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