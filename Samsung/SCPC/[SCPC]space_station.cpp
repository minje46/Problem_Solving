#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
#pragma warning(disable : 4996)

#define MAX 200001

using namespace std;

int Answer;
vector<int> graph[MAX];
queue<int> que;
bool visit[MAX];
//
void dfs(int cur, int dst, int cnt)
{
	if (cnt == 3)
	{

	}

	for (int i = 0; i < graph[cur].size(); i++)
	{
		dfs(cur, graph[cur][i], cnt + 1);
	}
}

void pruning(int node)
{
	if (visit[graph[node][0]] || visit[graph[node][1]])
		return;

	int x = graph[node][0];
	int y = graph[node][1];

	vector<int>::iterator it;
	it = find(graph[x].begin(), graph[x].end(), y);
	if (it != graph[x].end())		// x, y°¡ ¿¬°á true.
	{
		Answer++;
		visit[node] = true;
	}
}

int main(int argc, char** argv)
{
	int T, test_case;

	freopen("input_3.txt", "r", stdin);

	cin >> T;				// T = The number of test cases.
	for (test_case = 0; test_case < T; test_case++)
	{
		int N, M;				// N = The number of vertexes.				M = The number of edges.
		cin >> N >> M;

		for (int i = 0; i <= N; i++)
			graph[i].clear();
		que.empty();
		fill(visit, visit + N + 1, false);

		for (int i = 0; i < M; i++)
		{
			int u, v;			// u = source node.			v = destination node.
			cin >> u >> v;
			graph[u].push_back(v);
			graph[v].push_back(u);
		}
	
		for (int i = 1; i <= N; i++)
			if (graph[i].size() == 2)
				que.push(i);
		
		Answer = 0;
		while (!que.empty())
		{
			int node = que.front();
			que.pop();

			if (!visit[node])
				pruning(node);
				//dfs(node, node, 1);
		}

		cout << "Case #" << test_case + 1 << endl;
		cout << N - Answer << endl;
	}

	return 0;
}