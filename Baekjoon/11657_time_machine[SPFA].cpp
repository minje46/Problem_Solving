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
	in_que[1] = true;					// [queue�� �ִ� vertex�� check�ϴ� �뵵.]
	cnt[1]++;							// [vertex�� visit count�� ����.]	
	while (!que.empty())
	{
		auto dpt = que.front();		// Index of departure vertex.
		que.pop();
		in_que[dpt] = false;		// The vertex was popped right before. [queue���� pop�Ǿ��� ������, false�� ����.]

		for (int i = 0; i < graph[dpt].size(); i++)
		{
			auto dst = graph[dpt][i].first;		// Index of destination vertex.
			if (dist[dst] > dist[dpt] + graph[dpt][i].second)
			{
				dist[dst] = dist[dpt] + graph[dpt][i].second;

				if (!in_que[dst])			// [queue�� destination vertex�� �̹� �����ϴ��� Ȯ���Ѵ�.]
				{
					cnt[dst]++;			// [Visit count.]
					if (cnt[dst] >= N)	// It means there is negative cycle.
					{							// [N-1������ update�� �����Ѱ��� ����.]
						cycle = true;		// [N��°�� update�� �ִٴ� ���� cycle�� ����.]	
						return;
					}
					que.push(dst);		// [Update�� vertex�� edge�� Ȯ���ؾ� �ϱ� ����.]
					in_que[dst] = true;	// [queue�� push�Ǿ��⿡, true.]
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