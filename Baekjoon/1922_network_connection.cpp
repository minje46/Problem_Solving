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
		dist[i] = INF;				// [���� ��忡�� ��� ���� ���ϴ� ���� INF�� �ʱ�ȭ �ϰ� �����Ѵ�.]
	dist[1] = 0;					// Start edge is alwyas zero. 
									//[�ڽ��� ���� �ǵ��ƿ��� ���� ���ٰ� �����߱� ������, ���� ����� path�� 0���� ������ �� �ִ�.]
	for (int i = 1; i <= N; i++)	// Loop for departure's vertex. [���� ���� loop.]
	{
		int idx = -1, min_dist = INF;		// idx = index of smallest node.			min_dist = minimum distance from departure to destination vertex.
		for (int j = 1; j <= N; j++)			// Loop for destination's vertex. [���� ���� loop.]
		{											//[���� ������ �� �� �ִ� ��� vertex���� �Ѱ��� ���ڴٴ� ��.]
			if (!visited[j] && min_dist > dist[j])		// Condition for selecting proper vertex.
			{										// [������ node�� �߿��� ���� ���� cost�� node�� �����ϱ� ����. (+ �湮���� ���� node�� �߿���)]
				min_dist = dist[j];			// Update minimum distance to compare again in next loop.
				idx = j;							// [node�� ��ȣ(index)�� �����ϰ� �ִ� ��.]
			}
		}

		visited[idx] = true;					// Update the node was visited.
		answer += min_dist;					// For total distance of MST.
		for (int k = 1; k <= N; k++)		// [���õ� node���� �̵��� �� �ִ� node���� shortest path�� update.]
		{
			if (arr[idx][k] == 0)				// If there is adjacent vertex from selected node.
				continue;						// [���õ� node���� �̵��� �� �ִ� node���� shortest path�� update�ϱ� ���� ���� ����Ǿ��ִ��ĸ� Ȯ��.]
			dist[k] = min(arr[idx][k], dist[k]);
		}											// Compare original distance which it has had and new path from selected node. [Shortest path�� ����.]
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