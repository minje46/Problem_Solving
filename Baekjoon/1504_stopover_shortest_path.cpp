#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

int INF = 10000000;								// Max value. [Means to infinity.]
int N, E;												//	N = The number of edges.			E = The number of adjacent connections.
int arr[1001][1001];							// arr = Input as adjacent array.
int dist[1001];									// dist = To store shortest path from A to B.
bool visit[1001];								// visit = To figure out whether edge is already visited or not.

vector<int> Dijkstra(int start)					// Search each shortest path from start point to end point.
{
	for (int i = 1; i <= N; i++)					// Initialize distance array and visit array.
	{													// That's because this function is called many times.
		dist[i] = INF;
		visit[i] = false;
	}
	dist[start] = 0;								// Initialize the first case as start point.	

	for (int k = 1; k <= N; k++)				// Search all edges.	[출발 vertex.]
	{													// [양방향 Graph이기 때문에, priority queue가 아닌 직접 도착지 index를 찾기 위함.]
		int m = INF + 1;							// Initialize infinity variable.
		int x = -1;									// Initialize index variable.
		for (int i = 1; i <= N; i++)				// Search all paths from departure edge to whole of destination edges.[도착 vertext.]
		{
			if (visit[i] == false && m > dist[i])		// The smallest cost path among not visited edges.
			{														// 	[Visited하지 않은 edge들 중에서 가장 작은 distance를 가진 node를 다음 도착지로 선택.]
				m = dist[i];									// Update minimum distance.
				x = i;												// Update the index of node which has smallest cost.				
			}
		}

		visit[x] = true;								// Update it was visited.		
		for (int i = 1; i <= N; i++)
			if (dist[i] > dist[x] + arr[x][i])		// To figure out condition's shortest path.
				dist[i] = dist[x] + arr[x][i];		// [Smallest node로 선택한 start point에서 graph의 전체 노드를 하나씩 도착지로 shortest path를 비교.]
	}														
	return vector<int>(dist, dist + N + 1);		// [Graph의 node들의 각 shortest path를 기록하고 있는 distance array를 범위에 맞춰서 return.]
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin >> N >> E;									// Input of the number of edges and connections.
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++)
			arr[i][j] = INF;							// Initialize the whole of array.

	for (int i = 0; i < E; i++)
	{
		int a, b, c;										// Temporary variable.
		cin >> a >> b >> c;							// Input of start, end, cost.
		arr[a][b] = c;									// Build adjacent array.
		arr[b][a] = c;									// Bi-directed graph.	
	}

	int pass_a, pass_b;								
	cin >> pass_a >> pass_b;					// Input of through pass point.
	
	vector<int> d_start = Dijkstra(1);			// Distance from start point[=1] to other nodes.
	vector<int> d1 = Dijkstra(pass_a);			// Distance from first through point to other nodes.
	vector<int> d2 = Dijkstra(pass_b);			// Distance from second through point to other nodes.

	int path_a = d_start[pass_a] + d1[pass_b] + d2[N];		// Start -> first through point -> second through point -> End.
	int path_b = d_start[pass_b] + d2[pass_a] + d1[N];		// Start -> second through point -> first through point -> End.

	if (min(path_a, path_b) >= INF)				// If the minimum value is INF, it means there is no way to get destination passed through specific points.	
		cout << -1 << endl;
	else													// Search the only shortest path.		
		cout << min(path_a, path_b) << endl;
}