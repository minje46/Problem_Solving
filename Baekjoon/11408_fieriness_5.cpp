#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
#include<memory.h>

#define MAX 900				// The maximum size of graph.
#define WORK 400			// The temporary index to distinguish work and person in one range. [한 개의 범위 내에서 사람과 일을 구분하기 위함.]
#define INF 987654321	// The infinite value.

using namespace std;

int capacity[MAX][MAX];		// The memory of capacity. [i에서 j까지의 간선 용량.]
int flow[MAX][MAX];			// The memory of flow. [i에서 j까지 현재 흐르는 유량.]
int dist[MAX][MAX];			// The memory of distance. [i에서 j까지 이동하는데 드는 비용.]
vector<int>graph[MAX];		// The memory of graph. [Adjacent list를 통한 인접 여부 저장.]

int S = 0, T = 899;				// The initialization of S(Source) and T(Sink).
int tot_flow = 0, tot_cnt = 0;	// tot_flow = The maximum total flow.		tot_cnt = The maximum work we do. [할 수 있는 일의 최대 개수.]

void MCMF(int N, int M)		// To figure out the MCMF.
{
	while (true)						// Until there is no more augmenting path. [증가 경로가 없을 때 까지 반복.] or [최단거리, 접근 가능한 경로가 없는 경우.]
	{
		int prev[MAX], d[MAX];	// The memory of previous vertex and distance to get the vertex. [정점에 도착하기 까지의 cost와 거쳐서 온 직전의 정점을 기억.]
		bool in_que[MAX] = { false };	// The memory of controloing queue. [Queue에 해당 정점이 존재 하는지 관리하기 위한 메모리.]  
											// For implementing SPFA algorithm.
		queue<int>que;					// Do initialize.
		fill(prev, prev + MAX, -1);		
		fill(d, d + MAX, INF);

		d[S] = 0;						// Prepare the first case.
		in_que[S] = true;				// [SPFA를 위한 초기 작업.]
		que.push(S);
		while (!que.empty())		// There is no more vertex to check.
		{
			int cur = que.front();	// The current(present) node.		
			que.pop();
			in_que[cur] = false;		// This node was popped right before, so it should be modified as false. [Pop된 node는 수정.]

			for (auto next : graph[cur])	// The node which is able to accessed from current node.
			{										// [현재 노드에서 접근 가능한 모든 node들을 확인.]
				if (capacity[cur][next] - flow[cur][next] > 0 && d[next] > d[cur] + dist[cur][next])
				{									// [Flow 흘릴 수 있는지 와 최단 경로인지 확인.]
					d[next] = d[cur] + dist[cur][next];	// Update the shortest path with cost. [최단 경로 업데이트.]
					prev[next] = cur;			// [현재 노드를 거쳐서 다음 노드에 도착했다는 것을 저장.]

					if (!in_que[next])			// The next node is not in queue, it will be pushed.
					{								// [Queue에 node가 없는 경우만, push.]	
						que.push(next);		
						in_que[next] = true;
					}
				}
			}
		}
			
		if (prev[T] == -1)					// If there is no way to get sink node, it should be finished.
			break;								// [sink node로 갈 수 있는 경로가 없다면, 종료.]

		int f = INF;								// The memory of minimum flow to discharge.
		for (int i = T; i != S; i = prev[i])	// [찾은 shortest path의 T(Sink)->S(Source) 방향으로 거꾸로 prev를 이용해서 접근.]
			f = min(f, capacity[prev[i]][i] - flow[prev[i]][i]);	// [접근하면서, 가장 작은 flow(유량)을 저장. 최소 유량으로 흘려보내야 하므로..]

		for (int i = T; i != S; i = prev[i])	// [찾은 shortest path의 T(Sink)->S(Source) 방향으로 거꾸로 prev를 이용해서 접근.]
		{											// [출발 노드(prev[i]) -> 도착 노드(i) 방향으로 flow 와 cost를 계산.]
			tot_flow += f * dist[prev[i]][i];	// [minimum flow * cost.]
			flow[prev[i]][i] += f;			// [현재 흐르고 있는 유량을 관리하는 flow를 통해 현재(cur) 노드에서 다음(next) 노드로 흐르는 유량을 update.]
			flow[i][prev[i]] -= f;			// [f(u,v) = -f(v,u)의 network flow 성질을 기반으로 역방향(backward)으로 해당 유량만큼 흐를 수 있도록 update.]
		}
		tot_cnt++;								// The memory of total number of work we do. [할 수 있는 일의 양을 count.]
	}
}

int main(void)
{
	int N, M;								// N = The number of people.		D = The number of work types.
	cin >> N >> M;
	for (int i = 1; i <= N; i++)		// S와 직원을 연결
	{
		capacity[S][i] = 1;			// [i 사람이 맡을 수 있는 일 개수는 1개 이므로, i 사람 입장에서는 1개의 유량을 최대 가질 수 있다.]
		graph[S].push_back(i);	// Organanize the graph.
		graph[i].push_back(S);	// For backward graph. [역방향 간선을 위함.]
	}

	for (int i = 1; i <= M; i++)					// T와 일을 연결
	{
		capacity[WORK + i][T] = 1;			// [i 번째 일을 담당하는 것은 한명만 가능, i 일 입장에서는 1개의 유량을 가질 수 있다.]
		graph[WORK + i].push_back(T);	// Organanize the graph.
		graph[T].push_back(WORK + i);	// For backward graph. [역방향 간선을 위함.]
	}

	for (int i = 1; i <= N; i++)
	{
		int cnt;					// The number of work the person can do. [i 번째 사람이 할 수 있는 일의 개수.]
		cin >> cnt;
		while (cnt--)			
		{
			int task, cost;		// The work's number and cost. [i번째 사람이 할 수 있는 일의 번호와 비용.]
			cin >> task >> cost;

			capacity[i][WORK + task] = 1;		// [i 번째 사람이 해당 번호의 일을 할 수 있는 것. 일은 1명만 할당될 수 있기 때문에 유량은 1로 세팅.]
			dist[i][WORK + task] = cost;		// [i 번째 사람이 해당 번호의 일을 하는데 드는 비용.]	
			dist[WORK + task][i] = -cost;		// [Backward edge를 위한 -f(v,u)를 저장.]
			graph[i].push_back(WORK + task);		// Organanize the graph.
			graph[WORK + task].push_back(i);		// For backward graph. [역방향 간선을 위함.]
		}
	}

	MCMF(N, M);						// To figure out the MCMF.

	cout << tot_cnt << endl;		// The total number of work we can do.
	cout << tot_flow << endl;		// The maximum total flow.
}