#include<iostream>
#include<algorithm>
#include<memory.h>
#include<vector>
#include<queue>
	
#define MAX 502					// The maximum size of graph.
#define INF 987654321		// The infinite value.
#define FOOD 250				// The temporary index to distinguish food and person in one range. [한 개의 범위 내에서 사람과 음식을 구분하기 위함.]

using namespace std;

int capacity[MAX][MAX];		// The memory of capacity. [i에서 j까지의 간선 용량.]
int flow[MAX][MAX];			// The memory of flow. [i에서 j까지 현재 흐르는 유량.]
int work[MAX];					// The memory of index to search. [Blocking edge를 불필요하게 search할 필요 없도록 search할 vertex의 index 저장.]
int level[MAX];					// The memory of level graph.
vector<int>graph[MAX];		// The memory of graph. [Adjacent list를 통한 인접 여부 저장.]

int S = 0, T = 500;				// The initialization of S(Source) and T(Sink).

bool BFS()							//	To figure out the level graph could be organized or not. 
{										// [Level graph를 그릴 수 있는지 확인하는 것.]
	fill(level, level + MAX, -1);	// Initialize level memory to build a level graph again. [Level graph는 여러번 그릴 수 있기 때문에 초기화가 매번 필요하다.]
	level[S] = 0;					// Set the source level as 0. [S의 level은 항상 0으로 시작.]

	queue<int> que;				// To do bfs.
	que.push(S);
	while (!que.empty())		// [서로 연결되어 있는 node를 check하는 것.]
	{
		int cur = que.front();
		que.pop();

		for (auto next : graph[cur])	// [현재 노드에서 접근할 수 있는 모든 노드들을 하나씩 체크하는 것.]
		{
			if (level[next] == -1 && capacity[cur][next] - flow[cur][next] > 0)	// Check it is blocking edge or not.	
			{									// [Level이 아직 설정 안되었으며, 유량을 흘릴 수 있는지 확인.]
				level[next] = level[cur] + 1;	// [현재 노드보다 1 level 더 높게 세팅.]
				que.push(next);			
			}
		}
	}								// [return의 조건이 맞으면 true, 틀리면 false를 자동 반환.]
	return level[T] != -1;	// [T의 level이 초기값과 동일하다면, 이는 S->T의 경로가 더 이상 없다는 것을 의미.]
}

int DFS(int cur, int min_flow)			// To figure out the flow they can discharge. [흘릴 수 있는 유량을 계산.]
{
	if (cur == T)							// If the node is Sink node, it should be finished.
		return min_flow;					// [Sink에 도착했다면, Sink로 들어오는 유량을 return하면서 종료.]

	for (int &i = work[cur]; i < graph[cur].size(); i++)	// [Work는 현재(cur) 노드가 접근 가능한 여러 노드들 중 접근이 가능한 index를 저장하고 있다.]
	{											// [Work가 저장하고 있는 index 부터 시작함으로써, 현재(cur) 노드가 연결되어 있는 모든 노드를 처음부터 살필 필요가 X.]
		int next = graph[cur][i];		// [현재(cur)노드에서 접근 가능한 연결 노드(i)를 next에 저장.]
		
		if (level[next] == level[cur] + 1 && capacity[cur][next] - flow[cur][next] > 0)	// Check it is blocking edge or not.
		{										// [현재(cur) 노드에서 1 level만 더 높은 것인지, 유량의 여유가 있는지 확인하는 것.]
			int res = DFS(next, min(capacity[cur][next] - flow[cur][next], min_flow));	// [다음(next) 노드와 현재 보낼 수 있는 최저의 유량 값을 이용.]
			if (res > 0)						// [유량의 값이 0이 아니라는 것은, 흘릴 수 있는 유량이 존재하는 것을 의미.]
			{
				flow[cur][next] += res;	// [현재 흐르고 있는 유량을 관리하는 flow를 통해 현재(cur) 노드에서 다음(next) 노드로 흐르는 유량을 update.]
				flow[next][cur] -= res;	// [f(u,v) = -f(v,u)의 network flow 성질을 기반으로 역방향(backward)으로 해당 유량만큼 흐를 수 있도록 update.]
				
				return res;					// The flow it could be discharged. [흘릴 수 있는 유량의 값.]
			}
		}
	}
	return 0;									// There is no way to flow. [유량을 흘릴 수 있는 경우가 존재하지 않아, 유량의 값이 0이라는 것.]
}

int main(void)
{
	int N, K, D;							// N = The number of people.		K = The number of maximum plates.		D = The number of food types.
	cin >> N >> K >> D;
	for (int i = 1; i <= N; i++)
	{
		capacity[S][i] = K;			// [i 사람이 최대 가져갈 수 있는 접시의 개수는 K개 이므로, i 사람 입장에서는 K개의 유량을 최대 가질 수 있다.]
		graph[S].push_back(i);	// Organanize the graph.
		graph[i].push_back(S);	// For backward graph. [역방향 간선을 위함.]
	}

	for (int i = 1; i <= D; i++)
	{
		int max_num;					// The maximum plates of each cook. [음식이 요리될 수 있는 최대 가능치.]
		cin >> max_num;

		capacity[i + FOOD][T] = max_num;		// [i 번째 요리가 max_num 만큼만 요리될 수 있는 것이므로, i 요리 입장에서는 max_num개의 유량을 가질 수 있다.]
		graph[i + FOOD].push_back(T);			// Organanize the graph.
		graph[T].push_back(i + FOOD);			// For backward graph. [역방향 간선을 위함.]
	}

	for (int i = 1; i <= N; i++)
	{
		int cnt;
		cin >> cnt;						// The number of cooks the people can. [i 번째 사람이 요리할 수 있는 종류의 개수.]
		for (int j = 0; j < cnt; j++)	
		{
			int cook;					// The food's number. [i번째 사람이 요리할 수 있는 음식의 번호.]
			cin >> cook;
				
			capacity[i][cook + FOOD] = 1;			// [i 번째 사람이 해당 번호의 음식을 요리할 수 있는 것. 음식은 1접시만 만들 수 있기 때문에 유량은 1로 세팅.]
			graph[i].push_back(cook + FOOD);	// Organanize the graph.	
			graph[cook + FOOD].push_back(i);	// For backward graph. [역방향 간선을 위함.]
		}
	}

	int tot_flow = 0;					// The memory of maximum flow.
	while (BFS())						// To figure out the level graph could be organized or not. 			
	{										// [Level graph를 그릴 수 있는지 확인하는 것. T의 level이 초기값과 동일하다면, 이는 S->T의 경로가 더 이상 없다는 것을 의미.]
		fill(work, work + MAX, 0);	// [Level graph를 그리면서 매번 blocking edge가 변경되기 때문에, Work memory 재설정.] 
		while (true)						// Until there is no more augmenting path. [증가 경로가 없을 때 까지 반복.]
		{
			int flow = DFS(S, INF);	// To figure out the flow they can discharge. [흘릴 수 있는 유량을 계산.] 
			
			if (flow == 0)				// If there is no way to flow, it means there is no more augmenting path.
				break;					// [유량의 값이 0이라는 것은, S->T로 보낼 수 있는 경로가 더 이상 없다는 것을 의미한다.]
											// [이 상황에서 끝내는 것이 아니라, 현재 상태를 반영해서 level graph를 다시 그려야 한다.]
			tot_flow += flow;			// Total flow.
		}
	}

	cout << tot_flow << endl;		// Output of maximum flow.
}