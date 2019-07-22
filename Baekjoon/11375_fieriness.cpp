#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
#include<memory.h>

#define MAX 2001				// The maximum size of graph.
#define INF 987654321		// The infinite value.
#define WORK 1000			// The temporary index to distinguish food and person in one range. [�� ���� ���� ������ ����� ������ �����ϱ� ����.]

using namespace std;

int capacity[MAX][MAX];		// The memory of capacity. [i���� j������ ���� �뷮.]
int flow[MAX][MAX];			// The memory of flow. [i���� j���� ���� �帣�� ����.]
int idx[MAX];						// The memory of index to search. [Blocking edge�� ���ʿ��ϰ� search�� �ʿ� ������ search�� vertex�� index ����.]
int level[MAX];					// The memory of level graph.
vector<int>graph[MAX];		// The memory of graph. [Adjacent list�� ���� ���� ���� ����.]

int S = 0, T = MAX - 1;		// The initialization of S(Source) and T(Sink).

bool BFS()							//	To figure out the level graph could be organized or not. 
{										// [Level graph�� �׸� �� �ִ��� Ȯ���ϴ� ��.]
	fill(level, level + MAX, -1);// Initialize level memory to build a level graph again. [Level graph�� ������ �׸� �� �ֱ� ������ �ʱ�ȭ�� �Ź� �ʿ��ϴ�.]
	level[S] = 0;					// Set the source level as 0. [S�� level�� �׻� 0���� ����.]

	queue<int> que;				// To do bfs.
	que.push(S);
	while (!que.empty())		// [���� ����Ǿ� �ִ� node�� check�ϴ� ��.]
	{
		int cur = que.front();
		que.pop();

		for (auto next : graph[cur])	// [���� ��忡�� ������ �� �ִ� ��� ������ �ϳ��� üũ�ϴ� ��.]
		{
			if (level[next] == -1 && capacity[cur][next] - flow[cur][next] > 0)	// Check it is blocking edge or not.	
			{									// [Level�� ���� ���� �ȵǾ�����, ������ �긱 �� �ִ��� Ȯ��.]
				level[next] = level[cur] + 1;	// [���� ��庸�� 1 level �� ���� ����.]
				que.push(next);
			}
		}
	}								// [return�� ������ ������ true, Ʋ���� false�� �ڵ� ��ȯ.]
	return level[T] != -1;	// [T�� level�� �ʱⰪ�� �����ϴٸ�, �̴� S->T�� ��ΰ� �� �̻� ���ٴ� ���� �ǹ�.]
}

int DFS(int cur, int min_flow)			// To figure out the flow they can discharge. [�긱 �� �ִ� ������ ���.]
{
	if (cur == T)							// If the node is Sink node, it should be finished.
		return min_flow;					// [Sink�� �����ߴٸ�, Sink�� ������ ������ return�ϸ鼭 ����.]

	for (int &i = idx[cur]; i < graph[cur].size(); i++)	// [Work�� ����(cur) ��尡 ���� ������ ���� ���� �� ������ ������ index�� �����ϰ� �ִ�.]
	{											// [Work�� �����ϰ� �ִ� index ���� ���������ν�, ����(cur) ��尡 ����Ǿ� �ִ� ��� ��带 ó������ ���� �ʿ䰡 X.]
		int next = graph[cur][i];		// [����(cur)��忡�� ���� ������ ���� ���(i)�� next�� ����.]

		if (level[next] == level[cur] + 1 && capacity[cur][next] - flow[cur][next] > 0)	// Check it is blocking edge or not.
		{										// [����(cur) ��忡�� 1 level�� �� ���� ������, ������ ������ �ִ��� Ȯ���ϴ� ��.]
			int res = DFS(next, min(capacity[cur][next] - flow[cur][next], min_flow));	// [����(next) ���� ���� ���� �� �ִ� ������ ���� ���� �̿�.]
			if (res > 0)						// [������ ���� 0�� �ƴ϶�� ����, �긱 �� �ִ� ������ �����ϴ� ���� �ǹ�.]
			{
				flow[cur][next] += res;	// [���� �帣�� �ִ� ������ �����ϴ� flow�� ���� ����(cur) ��忡�� ����(next) ���� �帣�� ������ update.]
				flow[next][cur] -= res;	// [f(u,v) = -f(v,u)�� network flow ������ ������� ������(backward)���� �ش� ������ŭ �带 �� �ֵ��� update.]

				return res;					// The flow it could be discharged. [�긱 �� �ִ� ������ ��.]
			}
		}
	}
	return 0;									// There is no way to flow. [������ �긱 �� �ִ� ��찡 �������� �ʾ�, ������ ���� 0�̶�� ��.]
}

int main(void)
{
	int N, M;
	cin >> N >> M;
	for (int i = 1; i <= N; i++)
	{
		capacity[S][i] = 1;			// [i ����� �ִ� ������ �� �ִ� ������ ������ K�� �̹Ƿ�, i ��� ���忡���� K���� ������ �ִ� ���� �� �ִ�.]
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
			int task;				// The work's number. [i��° ����� �� �� �ִ� ���� ��ȣ.]
			cin >> task;

			capacity[i][WORK + task] = 1;			// [i ��° ����� �ش� ��ȣ�� ���� �� �� �ִ� ��. ���� 1�� �Ҵ�� �� �ֱ� ������ ������ 1�� ����.]
			graph[i].push_back(WORK + task);	// Organanize the graph.
			graph[WORK + task].push_back(i);	// For backward graph. [������ ������ ����.]
		}
	}

	int tot_flow = 0;					// The memory of maximum flow.
	while (BFS())						// To figure out the level graph could be organized or not. 			
	{										// [Level graph�� �׸� �� �ִ��� Ȯ���ϴ� ��. T�� level�� �ʱⰪ�� �����ϴٸ�, �̴� S->T�� ��ΰ� �� �̻� ���ٴ� ���� �ǹ�.]
		fill(idx, idx + MAX, 0);		// [Level graph�� �׸��鼭 �Ź� blocking edge�� ����Ǳ� ������, Work memory �缳��.] 
		while (true)						// Until there is no more augmenting path. [���� ��ΰ� ���� �� ���� �ݺ�.]
		{
			int flow = DFS(S, INF);	// To figure out the flow they can discharge. [�긱 �� �ִ� ������ ���.] 

			if (flow == 0)				// If there is no way to flow, it means there is no more augmenting path.
				break;					// [������ ���� 0�̶�� ����, S->T�� ���� �� �ִ� ��ΰ� �� �̻� ���ٴ� ���� �ǹ��Ѵ�.]
											// [�� ��Ȳ���� ������ ���� �ƴ϶�, ���� ���¸� �ݿ��ؼ� level graph�� �ٽ� �׷��� �Ѵ�.]
			tot_flow += flow;			// Total flow.
		}
	}

	cout << tot_flow << endl;		// Output of maximum flow.
}