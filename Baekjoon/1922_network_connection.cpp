#include<iostream>
#include<algorithm>

#define INF 987654321	// Initialize INFINITY.

using namespace std;

int arr[1001][1001];		// Memory of edge.
bool visited[1001];			// Memory of visited or not.
int dist[1001];				// Memory of distance.

int Prim(int N, int M)		// To figure minimum spanning tree.
{
	int answer = 0;			// Minimum cost of spanning tree.

	for (int i = 1; i <= N; i++)	// Initailize edge's distance as INFINITY.
		dist[i] = INF;				// [시작 노드에서 모든 노드로 향하는 길은 INF로 초기화 하고 시작한다.]
	dist[1] = 0;					// Start edge is alwyas zero. 
									//[자신의 노드로 되돌아오는 길은 없다고 가정했기 때문에, 시작 노드의 path는 0으로 고정할 수 있다.]
	for (int i = 1; i <= N; i++)	// Loop for departure's vertex. [시작 점의 loop.]
	{
		int idx = -1, min_dist = INF;		// idx = index of smallest node.			min_dist = minimum distance from departure to destination vertex.
		for (int j = 1; j <= N; j++)			// Loop for destination's vertex. [도착 점의 loop.]
		{											//[시작 점에서 갈 수 있는 모든 vertex들을 한개씩 보겠다는 것.]
			if (!visited[j] && min_dist > dist[j])		// Condition for selecting proper vertex.
			{										// [인접한 node들 중에서 가장 작은 cost의 node를 선택하기 위함. (+ 방문하지 않은 node들 중에서)]
				min_dist = dist[j];			// Update minimum distance to compare again in next loop.
				idx = j;							// [node의 번호(index)를 저장하고 있는 것.]
			}
		}

		visited[idx] = true;					// Update the node was visited.
		answer += min_dist;					// For total distance of MST.
		for (int k = 1; k <= N; k++)		// [선택된 node에서 이동할 수 있는 node로의 shortest path를 update.]
		{
			if (arr[idx][k] == 0)				// If there is adjacent vertex from selected node.
				continue;						// [선택된 node에서 이동할 수 있는 node로의 shortest path를 update하기 위해 서로 연결되어있느냐를 확인.]
			dist[k] = min(arr[idx][k], dist[k]);
		}											// Compare original distance which it has had and new path from selected node. [Shortest path를 선택.]
	}

	return answer;								// Total distance of MST.
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	int N, M;										// N = The number of vertex.		N = The number of line.
	cin >> N >> M;							// Input of N, M.

	for (int i = 0; i < M; i++)
	{
		int a, b, c;								// Temporary variables to store start node, end node, cost.		
		cin >> a >> b >> c;					// Input of start, end, cost.
		arr[a][b] = c;							// Build adjacent array.
		arr[b][a] = c;							// Bi-directed graph.
	}

	cout << Prim(N, M) << endl;			// To figure minimum spanning tree.
}