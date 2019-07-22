#include<iostream>
#include<algorithm>
#include<vector>

#define INF 987654321
#define MAX 502

using namespace std;

int dist[MAX];						// The memory of distance.	
bool cycle = true;				// To figure out whether there is negative cycle or not.

void Bellman_ford(int N, vector<pair<int,int>>graph[])				// To figure out the shortest path.
{
	for (int i = 0; i <= N; i++)	// Initialize each distance as INFINITY.
		dist[i] = INF;
	
	dist[1] = 0;			// Start point. [Initiation.]
	cycle = true;			// For while loop at first time. [Initiation.]
	int cnt = 0;				// Check the count to verify the negative cycle exists or not. [Initiation.]

	while (cycle && cnt != N)		// To check whether the negative cycle exists or not. 
	{										// [���� ��ȯ�� �ִ��� ���θ� Ȯ���ϱ� ���� ����. N��°�� distance update�� �ִٸ�, cycle ����.]
		cycle = false;					// Judge the negative value exists or not. [���� ����ġ�� ���ٸ�, ���� for loop�� ���� Relaxation ������ ��ģ ��, cycle=false���� ��ȭ�� ����.
											// 2��°, while loop ���Ŀ� false�� �ʱ�ȭ�� cycle�� �� �̻��� relaxation�� ���� ���̰�, negative cycle�� Ȯ���� ���� N�������� �ݺ��� ���� �� �ִ�.]
		cnt++;							// Counting the number of repeatition.
		for (int i = 1; i <= N; i++)	// From departure point.
		{									// [i�� vertex�� ó��(1��)���� ��(N��)���� check�ϴ� ��.]	
			for (auto j : graph[i])	// To destination point.
			{								// [j�� ��� vertex�� ����Ǿ��ִ� ���� vertex�� �ǹ�.]		
				if (dist[j.first] > dist[i] + j.second)	// j.first = destination.		j.second = cost.			dist[i] = departure.
				{
					dist[j.first] = dist[i] + j.second;	// Update the shortest path.
					cycle = true;								// Update the cycle's existence.
				}
			}
		}
	}
}

int main(void)
{
	int T, N, M, W;									// T = The test case.	N = The number of vertex.		M = The number of edges.	W = The cost.
	cin >> T;											
	while (T--)											// Test case.
	{
		vector<pair<int, int>>graph[MAX];	// The memory of graph.	

		cin >> N >> M >> W;						// Input of the number of vertex, edge, cost.	
		for (int i = 0; i < M; i++)
		{
			int s, e, t;									
			cin >> s >> e >> t;
			graph[s].push_back({ e, t });		// Organize the graph with edges. [Organize the roads between planets.]
			graph[e].push_back({ s, t });		// The roads are bi-directed.
		}
		for (int i = 0; i < W; i++)
		{
			int s, e, t;
			cin >> s >> e >> t;
			graph[s].push_back({ e, -t });		// Organize the graph with edges. [Organize the wormhole between planets.]
		}													// The wormhole is one way.

		Bellman_ford(N, graph);					// To figure out the shortest path.

		if (cycle)
			cout << "YES" << endl;				// Output.
		else
			cout << "NO" << endl;
	}
}