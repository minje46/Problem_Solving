#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
#include<memory.h>

#define MAX 900				// The maximum size of graph.
#define WORK 400			// The temporary index to distinguish work and person in one range. [�� ���� ���� ������ ����� ���� �����ϱ� ����.]
#define INF 987654321	// The infinite value.

using namespace std;

int capacity[MAX][MAX];		// The memory of capacity. [i���� j������ ���� �뷮.]
int flow[MAX][MAX];			// The memory of flow. [i���� j���� ���� �帣�� ����.]
int dist[MAX][MAX];			// The memory of distance. [i���� j���� �̵��ϴµ� ��� ���.]
vector<int>graph[MAX];		// The memory of graph. [Adjacent list�� ���� ���� ���� ����.]

int S = 0, T = 899;				// The initialization of S(Source) and T(Sink).
int tot_flow = 0, tot_cnt = 0;	// tot_flow = The maximum total flow.		tot_cnt = The maximum work we do. [�� �� �ִ� ���� �ִ� ����.]

void MCMF(int N, int M)		// To figure out the MCMF.
{
	while (true)						// Until there is no more augmenting path. [���� ��ΰ� ���� �� ���� �ݺ�.] or [�ִܰŸ�, ���� ������ ��ΰ� ���� ���.]
	{
		int prev[MAX], d[MAX];	// The memory of previous vertex and distance to get the vertex. [������ �����ϱ� ������ cost�� ���ļ� �� ������ ������ ���.]
		bool in_que[MAX] = { false };	// The memory of controloing queue. [Queue�� �ش� ������ ���� �ϴ��� �����ϱ� ���� �޸�.]  
											// For implementing SPFA algorithm.
		queue<int>que;					// Do initialize.
		fill(prev, prev + MAX, -1);		
		fill(d, d + MAX, INF);

		d[S] = 0;						// Prepare the first case.
		in_que[S] = true;				// [SPFA�� ���� �ʱ� �۾�.]
		que.push(S);
		while (!que.empty())		// There is no more vertex to check.
		{
			int cur = que.front();	// The current(present) node.		
			que.pop();
			in_que[cur] = false;		// This node was popped right before, so it should be modified as false. [Pop�� node�� ����.]

			for (auto next : graph[cur])	// The node which is able to accessed from current node.
			{										// [���� ��忡�� ���� ������ ��� node���� Ȯ��.]
				if (capacity[cur][next] - flow[cur][next] > 0 && d[next] > d[cur] + dist[cur][next])
				{									// [Flow �긱 �� �ִ��� �� �ִ� ������� Ȯ��.]
					d[next] = d[cur] + dist[cur][next];	// Update the shortest path with cost. [�ִ� ��� ������Ʈ.]
					prev[next] = cur;			// [���� ��带 ���ļ� ���� ��忡 �����ߴٴ� ���� ����.]

					if (!in_que[next])			// The next node is not in queue, it will be pushed.
					{								// [Queue�� node�� ���� ��츸, push.]	
						que.push(next);		
						in_que[next] = true;
					}
				}
			}
		}
			
		if (prev[T] == -1)					// If there is no way to get sink node, it should be finished.
			break;								// [sink node�� �� �� �ִ� ��ΰ� ���ٸ�, ����.]

		int f = INF;								// The memory of minimum flow to discharge.
		for (int i = T; i != S; i = prev[i])	// [ã�� shortest path�� T(Sink)->S(Source) �������� �Ųٷ� prev�� �̿��ؼ� ����.]
			f = min(f, capacity[prev[i]][i] - flow[prev[i]][i]);	// [�����ϸ鼭, ���� ���� flow(����)�� ����. �ּ� �������� ��������� �ϹǷ�..]

		for (int i = T; i != S; i = prev[i])	// [ã�� shortest path�� T(Sink)->S(Source) �������� �Ųٷ� prev�� �̿��ؼ� ����.]
		{											// [��� ���(prev[i]) -> ���� ���(i) �������� flow �� cost�� ���.]
			tot_flow += f * dist[prev[i]][i];	// [minimum flow * cost.]
			flow[prev[i]][i] += f;			// [���� �帣�� �ִ� ������ �����ϴ� flow�� ���� ����(cur) ��忡�� ����(next) ���� �帣�� ������ update.]
			flow[i][prev[i]] -= f;			// [f(u,v) = -f(v,u)�� network flow ������ ������� ������(backward)���� �ش� ������ŭ �带 �� �ֵ��� update.]
		}
		tot_cnt++;								// The memory of total number of work we do. [�� �� �ִ� ���� ���� count.]
	}
}

int main(void)
{
	int N, M;								// N = The number of people.		D = The number of work types.
	cin >> N >> M;
	for (int i = 1; i <= N; i++)		// S�� ������ ����
	{
		capacity[S][i] = 1;			// [i ����� ���� �� �ִ� �� ������ 1�� �̹Ƿ�, i ��� ���忡���� 1���� ������ �ִ� ���� �� �ִ�.]
		graph[S].push_back(i);	// Organanize the graph.
		graph[i].push_back(S);	// For backward graph. [������ ������ ����.]
	}

	for (int i = 1; i <= M; i++)					// T�� ���� ����
	{
		capacity[WORK + i][T] = 1;			// [i ��° ���� ����ϴ� ���� �Ѹ� ����, i �� ���忡���� 1���� ������ ���� �� �ִ�.]
		graph[WORK + i].push_back(T);	// Organanize the graph.
		graph[T].push_back(WORK + i);	// For backward graph. [������ ������ ����.]
	}

	for (int i = 1; i <= N; i++)
	{
		int cnt;					// The number of work the person can do. [i ��° ����� �� �� �ִ� ���� ����.]
		cin >> cnt;
		while (cnt--)			
		{
			int task, cost;		// The work's number and cost. [i��° ����� �� �� �ִ� ���� ��ȣ�� ���.]
			cin >> task >> cost;

			capacity[i][WORK + task] = 1;		// [i ��° ����� �ش� ��ȣ�� ���� �� �� �ִ� ��. ���� 1�� �Ҵ�� �� �ֱ� ������ ������ 1�� ����.]
			dist[i][WORK + task] = cost;		// [i ��° ����� �ش� ��ȣ�� ���� �ϴµ� ��� ���.]	
			dist[WORK + task][i] = -cost;		// [Backward edge�� ���� -f(v,u)�� ����.]
			graph[i].push_back(WORK + task);		// Organanize the graph.
			graph[WORK + task].push_back(i);		// For backward graph. [������ ������ ����.]
		}
	}

	MCMF(N, M);						// To figure out the MCMF.

	cout << tot_cnt << endl;		// The total number of work we can do.
	cout << tot_flow << endl;		// The maximum total flow.
}