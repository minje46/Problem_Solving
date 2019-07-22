#include <iostream>
#include <vector>
#include <queue>

# define INF 987654321				// Initialize INFINITY.

using namespace std;

struct Edge									// Memory structure of edge. 			
{
	int to;									// Where this edge is heading to.
	int cost;									// path's cost.
	Edge(int to, int cost) : to(to), cost(cost) { }	// Bit field.
};

vector<Edge> edge[20001];		// Memory of edge.
int dist[20001];							// Memory of distance.
bool visit[20001];					// Memory of visited or not.		

void Dijkstra(int V, int E, int start)	// Figure all edge's shortest path from start point.
{
	for (int i = 1; i <= V; i++)			// Initailize edge's distance as INFINITY.
		dist[i] = INF;						// [���� ��忡�� ��� ���� ���ϴ� ���� INF�� �ʱ�ȭ �ϰ� �����Ѵ�.]

	dist[start] = 0;						// Start edge is alwyas zero. 
												//[�ڽ��� ���� �ǵ��ƿ��� ���� ���ٰ� �����߱� ������, ���� ����� path�� 0���� ������ �� �ִ�.]
	priority_queue<pair<int, int>> que;		
	que.push(make_pair(0, start));	// Push the start point with cost 0. [cost 0�� ä�� start node�� priority queue�� push�Ѵ�.]

	while (!que.empty())				// Till there is no more node in queue.
	{
		auto idx = que.top();			// auto makes select data type automatically.
		que.pop();							// [Queue�� node�� pop�ϰ� �ش� edge�� connection ���θ� Ȯ���Ѵ�.]
		int x = idx.second;				// [Pop �� edge�� ��ȣ(index)�� �����Ѵ�.]
		if (visit[x])						// [�̹� �湮�� edge�� ���, pass �Ѵ�.]
			continue;						// [�̹� �湮�� edge�� ���, �̹� shortest path�� ������ �Ǿ��� ���̴�.]
												// [Dijkstra algorithm�� ���缺���� ������ �����ϴ�.]
		visit[x] = true;					// [A->B�� ���� path���� A->C->B�� �����ϴ� path���� not short�� ���,
												// Priority queue���� B�� �ƴ�, C�� top�� �����߾�� �Ѵ�.]
		for (int i = 0; i<edge[x].size(); i++)		// [�ش� edge�� ����� ������ ���� ��ŭ loop�� Ȯ���Ѵ�.]
		{
			int y = edge[x][i].to;						// [�ش� edge���� �������� ���ϴ� edge�� ��ġ ����.]
			if (dist[y] > dist[x] + edge[x][i].cost)	// [������ edge���� �����ϰ� �ִ� path�� ��������� ������������ path�� �հ� ���ؼ� shortest�� pick.]
			{
				dist[y] = dist[x] + edge[x][i].cost;
				que.push(make_pair(-dist[y], y));		// [first node�� distance ��꿡���� �ʿ� ������, 
			}														// Priority queue�� �ڵ� sorting�� ���� �ùٸ� �켱������ ������ ���ؼ� �ʿ��ϴ�.]	
		}
	}
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	
	int V, E, start;									// V = The number of vertex.		E = The number of line.			start = The start point.
	cin >> V >> E;								// Input of vertex and line.
	cin >> start;									// Input of start point.
	
	for (int i = 0; i<E; i++)
	{
		int x, y, z;									// Temporary variables to store start node, end node, cost.		
		cin >> x >> y >> z;						// Input of start, end, cost.
		edge[x].push_back(Edge(y, z));	// Store the each edge's vertex and cost in structure.	
	}

	Dijkstra(V, E, start);							// Figure out shortest path individually.

	for (int i = 1; i <= V; i++)					// All vertexs.
	{
		if (dist[i] >= INF)							// There is no connection between edges.	
			cout << "INF" << endl;				// Edges are initialized as INFIITY.	
		else
			cout << dist[i] << endl;			// Out put of edge's shortest path.
	}
}