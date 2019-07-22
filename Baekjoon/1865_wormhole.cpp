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
	{										// [음의 순환이 있는지 여부를 확인하기 위한 조건. N번째에 distance update가 있다면, cycle 존재.]
		cycle = false;					// Judge the negative value exists or not. [음의 가중치가 없다면, 이중 for loop를 통한 Relaxation 과정을 거친 후, cycle=false에서 변화가 없다.
											// 2번째, while loop 이후에 false로 초기화된 cycle은 더 이상의 relaxation이 없을 것이고, negative cycle의 확인을 위한 N번까지의 반복을 피할 수 있다.]
		cnt++;							// Counting the number of repeatition.
		for (int i = 1; i <= N; i++)	// From departure point.
		{									// [i는 vertex의 처음(1번)부터 끝(N번)까지 check하는 것.]	
			for (auto j : graph[i])	// To destination point.
			{								// [j는 출발 vertex에 연결되어있는 도착 vertex를 의미.]		
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