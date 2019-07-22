#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>

#define INF 987654321
#define MAX 502

using namespace std;

vector<pair<int, int>>graph[MAX];		// The memory of graph.	
int dist[MAX], cnt[MAX];						// The memory of distance and count of how many times the node was visited.
bool in_que[MAX], cycle = false;			// The memory of controlling queue and cycle.	

void SPFA(int N)						// To figure out the shortest path.
{
	for (int i = 1; i <= N; i++)		// Initialize each distance as INFINITY.
		dist[i] = INF;
	dist[1] = 0;						// Start point.

	queue<int> que;
	que.push(1);
	in_que[1] = true;					// [queue에 있는 vertex를 check하는 용도.]
	cnt[1]++;							// [vertex의 visit count를 관리.]	
	while (!que.empty())
	{
		auto dpt = que.front();		// Index of departure vertex.
		que.pop();
		in_que[dpt] = false;		// The vertex was popped right before. [queue에서 pop되었기 때문에, false로 수정.]

		for (int i = 0; i < graph[dpt].size(); i++)
		{
			auto dst = graph[dpt][i].first;		// Index of destination vertex.
			if (dist[dst] > dist[dpt] + graph[dpt][i].second)
			{
				dist[dst] = dist[dpt] + graph[dpt][i].second;

				if (!in_que[dst])			// [queue에 destination vertex가 이미 존재하는지 확인한다.]
				{
					cnt[dst]++;			// [Visit count.]
					if (cnt[dst] >= N)	// It means there is negative cycle.
					{							// [N-1번까지 update가 가능한것이 원리.]
						cycle = true;		// [N번째에 update가 있다는 것이 cycle의 증거.]	
						return;
					}
					que.push(dst);		// [Update된 vertex의 edge를 확인해야 하기 때문.]
					in_que[dst] = true;	// [queue에 push되었기에, true.]
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

	SPFA(N);

	if (cycle)							// If there is negative cnt.
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