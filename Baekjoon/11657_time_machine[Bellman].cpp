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
	
	for (int i = 1; i <= N; i++)					// Relax는 i=1 일 때 이미 다 끝난다.
	{													// [i=1 이후부터 확인하면서, update가 한번이라도 있으면 Negative cycle 있다고 판단하는 것이고 loop 바로 나옴.]
		for (int j = 1; j <= N; j++)				// Repeat relax process.
		{												// Relax process.
			for (auto idx : graph[j])
			{
				if (dist[j] != INF && dist[idx.first] > idx.second + dist[j])			// idx.first = destination.		idx.second = cost.			dist[j] = departure.
				{
					dist[idx.first] = idx.second + dist[j];
					if (i == N)						// Negative cycle exists.
					{									// [Negative cycle이 없다면, vertex에 도달하는 최단거리는 edge-1(=M)으로 구할 수 있어야 한다.]
						cycle = true;				// [그럼에도 불구하고, N(=M+1)번 째에서, shortest path의 update가 있었다는 것은 Negative cycle이 존재한다는 의미.]	
						break;						// [Performance 조금이라도 살려봐야지..]
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