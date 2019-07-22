#include<iostream>
#include<algorithm>
#include<vector>

#define INF 987654321
#define MAX 502

using namespace std;

vector<pair<int, int>>graph[MAX];		// The memory of graph.	
int dist[MAX];										// The memory of distance.
bool cycle = false;								// To figure out whether there is negative cycle or not.

void Bellman_ford(int N)						// To figure out the shortest path.
{
	for (int i = 1; i <= N; i++)					// Initialize each distance as INFINITY.
		dist[i] = INF;
	dist[1] = 0;									// Start point.
	
	for (int i = 1; i <= N; i++)					// Relax�� i=1 �� �� �̹� �� ������.
	{													// [i=1 ���ĺ��� Ȯ���ϸ鼭, update�� �ѹ��̶� ������ Negative cycle �ִٰ� �Ǵ��ϴ� ���̰� loop �ٷ� ����.]
		for (int j = 1; j <= N; j++)				// Repeat relax process.
		{												// Relax process.
			for (auto idx : graph[j])
			{
				if (dist[j] != INF && dist[idx.first] > idx.second + dist[j])			// idx.first = destination.		idx.second = cost.			dist[j] = departure.
				{
					dist[idx.first] = idx.second + dist[j];
					if (i == N)						// Negative cycle exists.
					{									// [Negative cycle�� ���ٸ�, vertex�� �����ϴ� �ִܰŸ��� edge-1(=M)���� ���� �� �־�� �Ѵ�.]
						cycle = true;				// [�׷����� �ұ��ϰ�, N(=M+1)�� °����, shortest path�� update�� �־��ٴ� ���� Negative cycle�� �����Ѵٴ� �ǹ�.]	
						break;						// [Performance �����̶� ���������..]
					}										
				}
			}
		}
	}
}

int main(void)
{
	int N, M;
	cin >> N >> M;					// N = The number of vertex.		M = The number of edges.
	for (int i = 0; i < M; i++)		// Input of edges.
	{
		int a, b, c;
		cin >> a >> b >> c;
		graph[a].push_back({ b, c });		// Organize the graph with edges.
	}

	Bellman_ford(N);

	if (cycle)							// If there is negative cycle.
		cout << -1 << endl;
	else
	{
		for (int i = 2; i <= N; i++)	// Without the start point.(dist[1]) 
		{
			if (dist[i] == INF)
				cout << -1 << endl;			// There is no way to get this vertex.
			else
				cout << dist[i] << endl;	// Shortes path to get this vertex. (dist[i])
		}
	}
}