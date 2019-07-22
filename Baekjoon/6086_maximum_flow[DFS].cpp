#include<iostream>
#include<algorithm>
#include<cstdio>
#include<memory.h>			// To use 'memset()'

#define MAX 52
#define INF 987654321

using namespace std;

int capacity[MAX][MAX];		// The memory of capacity. [i에서 j까지의 간선 용량.]
int visit[MAX];						// The memory of visited node. [visited node를 관리.]
int S, T;								// S = source. [출발지.]		T = Sink. [도착지.]

int CtoI(char c)					// To convert character to int.
{
	if (c <= 'Z')						// Upper case.
		return c - 'A';
	return c - 'a' + 26;			// Lower case.
}

int Ford_Fulkerson(int now, int flow)
{
	if (visit[now])		// If there is no way to get sink node, it should be finished.
		return 0;			// [sink node로 갈 수 있는 경로가 없다면, 종료.]

	if (now == T)		// If the current node is sink node, it should be finished. [current node가 sink node(destination)이라면, 종료.]
		return flow;		// Return the flow it could be. [흐를 수 있는 유량을 return.]

	visit[now] = 1;	// Check the visited node(= now node). [현재 node를 방문 했다고 체크.]	
	for (int i = 0; i < MAX; i++)
	{
		if (capacity[now][i] > 0)	// [흘릴 수 있는 유량의 capacity가 0 이상일 때만, Check.]
		{					// i = The current node number.
			int min_f;	// To check the minimum capacity to flow.	[Source->Sink로 유량이 흐를 때, 최소 값의 flow로 전달될 것이기 때문.]
			if (min_f = Ford_Fulkerson(i, min(capacity[now][i], flow)))	// [now -> i 로 흘릴 수 있는 유량과, 현재까지의 minimum flow와 비교해서 더 작은 값을 사용.]
			{												// [흘러나간 유량이, 다시 들어오는 것이므로, capactity는 보존.]
				capacity[i][now] += min_f;		// [minimum flow를 backward search를 통해, update.]
				capacity[now][i] -= min_f;		// [정방향에서 흘릴 수 있는 유량은 updated된 만큼, 감소.]
				return min_f;							// [흘릴 수 있는 유량은 가장 작은 유량으로 결정.]
			}
		}
	}
	return 0;
}

int main(void)
{
	S = CtoI('A');	T = CtoI('Z');
	int N;						// N = The number of pipe.
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		char u, v;
		int w;
		cin >> u >> v >> w;		// Input of departure and destination vertex and capacity of pipe.

		u = CtoI(u);			// Convert the character to integer.
		v = CtoI(v);			// [array로 저장하기 위한 정수형 변환.]
		capacity[u][v] = capacity[v][u] += w;	// Set the capacity of pipe. [동일한 파이프 경로로 여러번 input 있을 수 있기 때문에, +=을 사용.]
	}

	int total = 0;			// Total flow. [최대로 흐를 수 있는 총 유량.]	
	while (1)					// Until there is no more augmenting path. [증가 경로가 없을 때 까지 반복.]
	{
		memset(visit, 0, sizeof(visit));	// Initiation.
		int flow = Ford_Fulkerson(0, INF);	// To figure out how much is the maximum flow we can discharge. [최대 유량 파악.]
		
		if (flow == 0)		// If there is no way to get sink node, it should be finished.
			break;			// [sink node로 갈 수 있는 경로가 없다면, 종료.]
		
		total += flow;		// Update the total flow. 
	}							// [Source->Sink로 흘를 수 있는 path가 여러개 존재할 수 있으므로, 총 유량을 따로 저장.]
	cout << total << endl;		// Output of total flow. [S->T로 흐를 수 있는 최대 유량.]
}