#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

#define INF 987654321						// Initialize INFINITY.
#define MAX 502									// Initialize MAX.

using namespace std;

vector<pair<int, int>> edge[MAX];		// Memory of edge.
vector<int> hist[MAX];							// Memory of previous edge's.
bool visited[MAX];								// Memory of visited or not.
int dist[MAX];										// Memory of distance.

int Dijkstra(int N, int start, int end)			// To figure out how the network will be restored.
{
	for (int i = 0; i < N; i++)					// Initialize memory.
	{
		dist[i] = INF;								// Set each distance as INFINITY.
		visited[i] = false;							// Set each edge's visited as false.
	}
	dist[start] = 0;								// Start edge is alwyas zero. 
													//[�ڽ��� ���� �ǵ��ƿ��� ���� ���ٰ� �����߱� ������, ���� ����� path�� 0���� ������ �� �ִ�.]
	priority_queue<pair<int, int>> que;		// Push the start point with cost 0. [cost 0�� ä�� start node�� priority queue�� push�Ѵ�.]
	que.push(make_pair(0, start));
	while (!que.empty())						// Till there is no more node in queue.
	{
		auto idx = que.top();					// auto sets data type automatically.
		que.pop();
		int dpt = idx.second;

		if (visited[dpt])							// [�̹� �湮�� edge�� ���, pass �Ѵ�. �̹� �湮�� edge�� ���, �̹� shortest path�� ������ �Ǿ��� ���̴�.]
			continue;								// [Dijkstra algorithm�� ���缺���� ������ �����ϴ�.]
		visited[dpt] = true;						// [A->B�� ���� path���� A->C->B�� �����ϴ� path���� not short�� ���, Priority queue���� B�� �ƴ�, C�� top�� �����߾�� �Ѵ�.]

		for (int i = 0; i < edge[dpt].size(); i++)	// [�ش� edge�� ����� ������ ���� ��ŭ loop�� Ȯ���Ѵ�.]
		{
			int dst = edge[dpt][i].first;				// [�ش� edge���� �������� ���ϴ� node�� ��ȣ ����.]
			if (dist[dst] > dist[dpt] + edge[dpt][i].second && edge[dpt][i].second != -1)		// [cost = -1�� ����, delete�� ������ �ǹ�.]
			{													// [������ edge���� �����ϰ� �ִ� path�� ��������� ������������ path�� �հ� ���ؼ� shortest�� pick.]
				dist[dst] = dist[dpt] + edge[dpt][i].second;	// Update shortest path.
				que.push(make_pair(-dist[dst], dst));

				hist[dst].clear();							// [������ hist�� ����Ǿ� �ִ� edge�� �ִ���, �ִ� ��ΰ� update�Ǿ��� ������ �ʱ�ȭ�� �ʿ�.]	
				hist[dst].push_back(dpt);				// [Destination���� ���� path�� previous edge�� cost�� hist�� ����.]
			}
			// If there is another shortest path which has same cost. [�ִ� ��ΰ� ������ ���� ���.]
			else if (dist[dst] == dist[dpt] + edge[dpt][i].second && edge[dpt][i].second != -1)
				hist[dst].push_back(dpt);			// [Destination���� ���� ��� shortest path�� �����ϰ� �־�� BFS�� Ž���� �����ϴ�.]
		}
	}
	if (dist[end] == INF)		// It means there is no path to get destination.
		return -1;

	else
		return dist[end];			// Return the shortest path.
}

void BFS(int end)				// To figure out what is the previous edge from destination edge using BFS search.
{
	queue<int> que;				// [BFS Ž���� ���� ���� ������ ��� node(edge)�� queue�� �����Ѵ�.]
	que.push(end);
	while (!que.empty())		// Till there is no more node in queue.
	{									// [Destination���� �����ϴ� path�� �Ųٷ� ��¤��� ����̴�.]
		int dpt = que.front();	// [�׷���, destination(end)�� departure edge�� ������ �ȴ�.]
		que.pop();

		for (int i = 0; i < hist[dpt].size(); i++)		// [Destination���� ������ �� �ִ� ��� edge�� search�ؾ��Ѵ�.]
		{											// vector<pair<int, int>>hist = <previous edge, cost> �� ����.
			int dst = hist[dpt][i];			// [previous edge�� destination���� set�ؼ� �Ųٷ� ã�ư��� ��.]

			for (int i = 0; i < edge[dst].size(); i++)	// [destination edge�� ������ edge���� ���� ������ ��� path�� search�ϱ� ����.]
				if (edge[dst][i].first == dpt)				// [edge[dst][i].first �� previous edge���� destination���� �� �� �ִ� edge�� ����.]
					edge[dst][i].second = -1;			// [Shortest path�� �Ǵ� edge�� ã�Ҵٸ�, �ش� path�� delete�ϱ� ���� -1�� ����.]
														// [Dijkstra algorithm�� ���� cost�� ������� �ʱ� ������, -1�� ������ �����ٰ� ���� �� �ִ�.]
			que.push(dst);					// [Previous edge ���� � edge�� ���ļ� ���� �� �ֱ� ������, BFS Ž���� �ʿ�.]
		}
	}
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	int N, M;

	while (true)
	{
		cin >> N >> M;					// Input of the number of edges and connections.
		if (N == 0 && M == 0)			// Exit condition.
			break;

		for (int i = 0; i < MAX; i++)	// Initialize again for each test case.
			edge[i].clear();				// Clear the edge memory.
		memset(hist, 0, sizeof(hist));		// Clear previous edge's memory.

		int start, end;
		cin >> start >> end;				// Input of start and end point.
		for (int i = 0; i < M; i++)
		{
			int u, v, p;
			cin >> u >> v >> p;
			edge[u].push_back(make_pair(v, p));
		}

		Dijkstra(N, start, end);			// To set shortest path on graph. [Graph�� shortest path�� set�ϱ� ����, dijkstra algorithm�� ���ȴ�.]

		BFS(end);							// To rebuild graph without shortest path. [�ִ� ��θ� ���� graph�� update�� �ʿ��ϱ⿡ BFS�� ����Ѵ�.]

		cout << Dijkstra(N, start, end) << endl;		// Output of almost shortest path.
	}
}
