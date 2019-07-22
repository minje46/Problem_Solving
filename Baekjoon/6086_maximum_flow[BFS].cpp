#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>

#define MAX 52
#define INF 987654321

using namespace std;

int capacity[MAX][MAX];		// The memory of capacity. [i에서 j까지의 간선 용량.]
int flow[MAX][MAX];			// The memory of flow. [i에서 j까지 현재 흐르는 유량.]
vector<int>graph[MAX];		// The memory of graph. [Adjacent list를 통한 인접 여부 저장.]

int CtoI(char c)					// To convert character to int.
{
	if (c <= 'Z')						// Upper case.
		return c - 'A';
	return c - 'a' + 26;			// Lower case.
}

int Ford_Fulkerson(int N)
{
	int total = 0;							// Total flow. [최대로 흐를 수 있는 총 유량.]	
	int S = CtoI('A'), T = CtoI('Z');	// S = source. [출발지.]		T = Sink. [도착지.]
	while (true)								// Until there is no more augmenting path. [증가 경로가 없을 때 까지 반복.]
	{
		int prev[MAX];					// To do backward search. [역방향 검색을 하기 위한 memory.]
		fill(prev, prev + MAX, -1);		// [prev[]에 방문했던 node를 저장.]

		queue<int>que;
		que.push(S);						// BFS search.
		while (!que.empty() && prev[T] == -1)
		{  
			int cur = que.front();
			que.pop();
			for (int next : graph[cur])	// It is for checking next node which is connected from current node.		
			{				// [cur node에서 연결된 node들을 next node로 인지하기 위함.]
				if (capacity[cur][next] - flow[cur][next] > 0 && prev[next] == -1)	 // [c[i][j]-f[i][j]>0은  i에서 j로 유량을 흘릴 수 있는지 판단.]
				{			// [prev[next] == -1라는 것은 next node를 아직 방문하지 않았다는 것.]
					que.push(next);		// [조건에 맞았기 때문에, next node를 queue에 저장.]
					prev[next] = cur;		// [next node는 current node를 통해서 방문되었다고 cur를 저장.]

					if (next == T)			// If the next node is sink node, it should be finished.
						break;				// [next node가 sink node(destination)이라면, 종료.]
				}
			}
		}
		if (prev[T] == -1)				// If there is no way to get sink node, it should be finished.
			break;							// [sink node로 갈 수 있는 경로가 없다면, 종료.]

		int min_f = INF;					// To check the minimum capacity to flow.
		for (int i = T; i != S; i = prev[i])		// [흘릴 수 있는 유량은 가장 작은 유량으로 결정.]
			min_f = min(min_f, capacity[prev[i]][i] - flow[prev[i]][i]);	// [Sink node -> Source node로 역방향 추적.]
		
		for (int i = T; i != S; i = prev[i])		// Update the flow.
		{
			flow[prev[i]][i] += min_f;		// [minimum flow를 backward search를 통해, update.]
			flow[i][prev[i]] -= min_f;		// [정방향에서 흘릴 수 있는 유량은 updated된 만큼, 감소.]
		}												// [prev[i]->i 만큼 흘러나간 유량이, [i]->prev[i] 만큼 다시 들어오는 것이므로, capactity는 보존.]
		total += min_f;							// Update the total flow. [Source->Sink로 흘를 수 있는 path가 여러개 존재할 수 있으므로, 총 유량을 따로 저장.]
	}
	return total;
}

int main(void)
{
	int N;								// N = The number of pipe.
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		char u, v;
		int w;
		cin >> u >> v >> w;		// Input of departure and destination vertex and capacity of pipe.

		u = CtoI(u);					// Convert the character to integer.
		v = CtoI(v);					// [array로 저장하기 위한 정수형 변환.]	
		capacity[u][v] = capacity[v][u] += w;	// Set the capacity of pipe. [동일한 파이프 경로로 여러번 input 있을 수 있기 때문에, +=을 사용.]
		graph[u].push_back(v);	// Organanize the graph.
		graph[v].push_back(u);	// For backward graph. [역방향 간선을 위함.]
	}

	cout << Ford_Fulkerson(N) << endl;		// Output of total flow. [S->T로 흐를 수 있는 최대 유량.]
}