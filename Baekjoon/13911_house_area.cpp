#include<iostream>
#include<algorithm>
#include<memory.h>
#include<vector>

#define MAX 10001
#define INF 987654321

using namespace std;

struct Node
{
	int node;
	int dist;
	bool visit;
};

int V, E;				// V = The number of vertexes.				E = The number of edges.
int M, X;				// M = The number of MacDonald.			X = The criteria of influential area.
int S, Y;				// S = The number of StarBucks.			Y = The criteria of influential area.
//int map[MAX][MAX];		// map = The memory of input data.
//bool visit[MAX][MAX];		// visit = The memory of visited or not.
vector<Node> map[MAX];
int check[MAX];
pair<int, int> cand[MAX];

void Init()
{
	for (int i = 0; i < MAX; i++)
	{
		check[i] = 1;
		cand[i] = { INF, INF };
	}
}

int Compare()
{
	int idx = 0, big = INF;
	for (int i = 1; i <= V; i++)
	{
		if (check[i] != 1)		// Take care only house.
			continue;

		if (cand[i].first == INF || cand[i].second == INF)		// Take care only influential area.
			continue;

		int tot = cand[i].first + cand[i].second;
		if (big > tot)
		{
			idx = i;
			big = tot;
		}
	}
	if (idx == 0)
		big = -1;

	return big;
}

void DFS(int dpt, int cur, int cnt)
{
	if (cnt> X || cnt > Y)
		return;

	if (check[cur] != 1)			// Not house.
	{
		if (check[cur] == -1)	// MacDonald.
			cand[dpt].first = min(cand[dpt].first, cnt);
		else							// StarBucks.
			cand[dpt].second = min(cand[dpt].second, cnt);
		return;
	}

	for (int i = 0; i < map[cur].size(); i++)
	{
		if (!map[cur][i].visit)
		{
			map[cur][i].visit = true;
			DFS(dpt, map[cur][i].node, cnt + map[cur][i].dist);
			map[cur][i].visit = false;
		}
	}
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);	cout.tie(0);
	
	Init();

	cin >> V >> E;
	for (int i = 0; i < E; i++)
	{
		int u, v, w;
		cin >> u >> v >> w;
		map[u].push_back({ v,w,false });
		map[v].push_back({ u,w,false });
	}
	cin >> M >> X;
	for (int i = 0; i < M; i++)
	{
		int m;
		cin >> m;
		check[m] = -1;
	}
	cin >> S >> Y;
	for (int i = 0; i < S; i++)
	{
		int s;
		cin >> s;
		check[s] = 0;
	}

	for (int i = 1; i <= V; i++)
	{
		if (check[i] == 1)
			DFS(i, i, 0);
	}
	int answer = Compare();
	cout << answer << endl;
}