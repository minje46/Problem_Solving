#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>

#define MAX 52
#define INF 987654321

using namespace std;

int capacity[MAX][MAX];		// The memory of capacity. [i���� j������ ���� �뷮.]
int flow[MAX][MAX];			// The memory of flow. [i���� j���� ���� �帣�� ����.]
vector<int>graph[MAX];		// The memory of graph. [Adjacent list�� ���� ���� ���� ����.]

int CtoI(char c)					// To convert character to int.
{
	if (c <= 'Z')						// Upper case.
		return c - 'A';
	return c - 'a' + 26;			// Lower case.
}

int Ford_Fulkerson(int N)
{
	int total = 0;							// Total flow. [�ִ�� �带 �� �ִ� �� ����.]	
	int S = CtoI('A'), T = CtoI('Z');	// S = source. [�����.]		T = Sink. [������.]
	while (true)								// Until there is no more augmenting path. [���� ��ΰ� ���� �� ���� �ݺ�.]
	{
		int prev[MAX];					// To do backward search. [������ �˻��� �ϱ� ���� memory.]
		fill(prev, prev + MAX, -1);		// [prev[]�� �湮�ߴ� node�� ����.]

		queue<int>que;
		que.push(S);						// BFS search.
		while (!que.empty() && prev[T] == -1)
		{  
			int cur = que.front();
			que.pop();
			for (int next : graph[cur])	// It is for checking next node which is connected from current node.		
			{				// [cur node���� ����� node���� next node�� �����ϱ� ����.]
				if (capacity[cur][next] - flow[cur][next] > 0 && prev[next] == -1)	 // [c[i][j]-f[i][j]>0��  i���� j�� ������ �긱 �� �ִ��� �Ǵ�.]
				{			// [prev[next] == -1��� ���� next node�� ���� �湮���� �ʾҴٴ� ��.]
					que.push(next);		// [���ǿ� �¾ұ� ������, next node�� queue�� ����.]
					prev[next] = cur;		// [next node�� current node�� ���ؼ� �湮�Ǿ��ٰ� cur�� ����.]

					if (next == T)			// If the next node is sink node, it should be finished.
						break;				// [next node�� sink node(destination)�̶��, ����.]
				}
			}
		}
		if (prev[T] == -1)				// If there is no way to get sink node, it should be finished.
			break;							// [sink node�� �� �� �ִ� ��ΰ� ���ٸ�, ����.]

		int min_f = INF;					// To check the minimum capacity to flow.
		for (int i = T; i != S; i = prev[i])		// [�긱 �� �ִ� ������ ���� ���� �������� ����.]
			min_f = min(min_f, capacity[prev[i]][i] - flow[prev[i]][i]);	// [Sink node -> Source node�� ������ ����.]
		
		for (int i = T; i != S; i = prev[i])		// Update the flow.
		{
			flow[prev[i]][i] += min_f;		// [minimum flow�� backward search�� ����, update.]
			flow[i][prev[i]] -= min_f;		// [�����⿡�� �긱 �� �ִ� ������ updated�� ��ŭ, ����.]
		}												// [prev[i]->i ��ŭ �귯���� ������, [i]->prev[i] ��ŭ �ٽ� ������ ���̹Ƿ�, capactity�� ����.]
		total += min_f;							// Update the total flow. [Source->Sink�� �긦 �� �ִ� path�� ������ ������ �� �����Ƿ�, �� ������ ���� ����.]
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
		v = CtoI(v);					// [array�� �����ϱ� ���� ������ ��ȯ.]	
		capacity[u][v] = capacity[v][u] += w;	// Set the capacity of pipe. [������ ������ ��η� ������ input ���� �� �ֱ� ������, +=�� ���.]
		graph[u].push_back(v);	// Organanize the graph.
		graph[v].push_back(u);	// For backward graph. [������ ������ ����.]
	}

	cout << Ford_Fulkerson(N) << endl;		// Output of total flow. [S->T�� �带 �� �ִ� �ִ� ����.]
}