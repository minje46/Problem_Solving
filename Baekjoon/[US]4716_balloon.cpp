#include<iostream>
#include<algorithm>
#include<queue>
#include<vector>
#include<memory.h>

#define MAX 1000
#define INF 987654321
#define A_BAL 1001
#define B_BAL 1002

using namespace std;

int capacity[MAX][MAX];		// The memory of capacity. [i���� j������ ���� �뷮.]
int flow[MAX][MAX];			// The memory of flow. [i���� j���� ���� �帣�� ����.]
int dist[MAX][MAX];			// The memory of distance. [i���� j���� �̵��ϴµ� ��� ���.]
vector<int>graph[MAX];		// The memory of graph. [Adjacent list�� ���� ���� ���� ����.]

int S = 0, T = MAX-1;				// The initialization of S(Source) and T(Sink).
int tot_flow = 0;					// tot_flow = The maximum total flow.[�� �� �ִ� ���� �ִ� ����.]

void MCMF(int N, int A, int B)
{
	while (true)
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
	}
}

int main(void)
{
	int N, A, B;
	while (true)
	{
		cin >> N >> A >> B;
		if (N == 0 && A == 0 && B == 0)
			break;
		
		for (int i = 1; i <= N; i++)
		{
			capacity[A_BAL][T] = A;
			capacity[B_BAL][T] = B;

			graph[A_BAL].push_back(T);
			graph[T].push_back(A_BAL);
			graph[B_BAL].push_back(T);
			graph[T].push_back(B_BAL);
		}

		for (int i = 1; i <= N; i++)
		{
			int k, u, v;
			cin >> k >> u >> v;

			capacity[S][i] = k;
			graph[S].push_back(i);
			graph[i].push_back(S);

			capacity[i][A_BAL] = k;
			capacity[i][B_BAL] = k;
			dist[i][A_BAL] = u;
			dist[A_BAL][i] = -u;
			dist[i][B_BAL] = v;
			dist[B_BAL][i] = -v;
			graph[i].push_back(A_BAL);
			graph[A_BAL].push_back(i);
			graph[i].push_back(B_BAL);
			graph[B_BAL].push_back(i);
		}

		MCMF(N, A, B);

		cout << tot_flow << endl;
	}
}