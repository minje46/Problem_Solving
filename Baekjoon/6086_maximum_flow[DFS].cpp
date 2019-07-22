#include<iostream>
#include<algorithm>
#include<cstdio>
#include<memory.h>			// To use 'memset()'

#define MAX 52
#define INF 987654321

using namespace std;

int capacity[MAX][MAX];		// The memory of capacity. [i���� j������ ���� �뷮.]
int visit[MAX];						// The memory of visited node. [visited node�� ����.]
int S, T;								// S = source. [�����.]		T = Sink. [������.]

int CtoI(char c)					// To convert character to int.
{
	if (c <= 'Z')						// Upper case.
		return c - 'A';
	return c - 'a' + 26;			// Lower case.
}

int Ford_Fulkerson(int now, int flow)
{
	if (visit[now])		// If there is no way to get sink node, it should be finished.
		return 0;			// [sink node�� �� �� �ִ� ��ΰ� ���ٸ�, ����.]

	if (now == T)		// If the current node is sink node, it should be finished. [current node�� sink node(destination)�̶��, ����.]
		return flow;		// Return the flow it could be. [�带 �� �ִ� ������ return.]

	visit[now] = 1;	// Check the visited node(= now node). [���� node�� �湮 �ߴٰ� üũ.]	
	for (int i = 0; i < MAX; i++)
	{
		if (capacity[now][i] > 0)	// [�긱 �� �ִ� ������ capacity�� 0 �̻��� ����, Check.]
		{					// i = The current node number.
			int min_f;	// To check the minimum capacity to flow.	[Source->Sink�� ������ �带 ��, �ּ� ���� flow�� ���޵� ���̱� ����.]
			if (min_f = Ford_Fulkerson(i, min(capacity[now][i], flow)))	// [now -> i �� �긱 �� �ִ� ������, ��������� minimum flow�� ���ؼ� �� ���� ���� ���.]
			{												// [�귯���� ������, �ٽ� ������ ���̹Ƿ�, capactity�� ����.]
				capacity[i][now] += min_f;		// [minimum flow�� backward search�� ����, update.]
				capacity[now][i] -= min_f;		// [�����⿡�� �긱 �� �ִ� ������ updated�� ��ŭ, ����.]
				return min_f;							// [�긱 �� �ִ� ������ ���� ���� �������� ����.]
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
		v = CtoI(v);			// [array�� �����ϱ� ���� ������ ��ȯ.]
		capacity[u][v] = capacity[v][u] += w;	// Set the capacity of pipe. [������ ������ ��η� ������ input ���� �� �ֱ� ������, +=�� ���.]
	}

	int total = 0;			// Total flow. [�ִ�� �带 �� �ִ� �� ����.]	
	while (1)					// Until there is no more augmenting path. [���� ��ΰ� ���� �� ���� �ݺ�.]
	{
		memset(visit, 0, sizeof(visit));	// Initiation.
		int flow = Ford_Fulkerson(0, INF);	// To figure out how much is the maximum flow we can discharge. [�ִ� ���� �ľ�.]
		
		if (flow == 0)		// If there is no way to get sink node, it should be finished.
			break;			// [sink node�� �� �� �ִ� ��ΰ� ���ٸ�, ����.]
		
		total += flow;		// Update the total flow. 
	}							// [Source->Sink�� �긦 �� �ִ� path�� ������ ������ �� �����Ƿ�, �� ������ ���� ����.]
	cout << total << endl;		// Output of total flow. [S->T�� �带 �� �ִ� �ִ� ����.]
}