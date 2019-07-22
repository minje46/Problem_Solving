#include<iostream>
#include<vector>
#include<queue>

#define INF 987654321					// Initialize INFINITY.

using namespace std;

vector<pair<int, int>> restoration;		// Memory of vertex history.
vector<pair<int, int>> edge[1001];	// Memory of edge.
bool visited[1001];							// Memory of visited or not.	
int dist[1001];								// Memory of distance.

void Dijkstra(int N, int M)					// To figure out how the network will be restored.
{
	int prev = -1;								// Memory of start point's index. [�������� index�� �����ϱ� ����.]	

	for (int i = 1; i <= N; i++)				// Initailize edge's distance as INFINITY.
		dist[i] = INF;							// [���� ��忡�� ��� ���� ���ϴ� ���� INF�� �ʱ�ȭ �ϰ� �����Ѵ�.]
	dist[1] = 0;								// Start edge is alwyas zero. 
													//[�ڽ��� ���� �ǵ��ƿ��� ���� ���ٰ� �����߱� ������, ���� ����� path�� 0���� ������ �� �ִ�.]
	priority_queue<pair<int, int>> que;	// Push the start point with cost 0. [cost 0�� ä�� start node�� priority queue�� push�Ѵ�.]
	que.push(make_pair(0, 1));			// Pair<distance, destination> �� ����.
	while (!que.empty())					// Till there is no more node in queue.
	{
		auto idx = que.top();				// auto makes select data type automatically.
		que.pop();								// [Queue�� node�� pop�ϰ� �ش� edge�� connection ���θ� Ȯ���Ѵ�.]

		if (visited[idx.second])				// [�̹� �湮�� edge�� ���, pass �Ѵ�. �̹� �湮�� edge�� ���, �̹� shortest path�� ������ �Ǿ��� ���̴�.]
			continue;							// [Dijkstra algorithm�� ���缺���� ������ �����ϴ�.]
		visited[idx.second] = true;		// [A->B�� ���� path���� A->C->B�� �����ϴ� path���� not short�� ���, Priority queue���� B�� �ƴ�, C�� top�� �����߾�� �Ѵ�.]
		
		for (int i = 0; i < edge[idx.second].size(); i++)	// [�ش� edge�� ����� ������ ���� ��ŭ loop�� Ȯ���Ѵ�.]
		{
			int y = edge[idx.second][i].first;					// [�ش� edge���� �������� ���ϴ� node�� ��ȣ ����.]
			if (dist[y] > dist[idx.second] + edge[idx.second][i].second)
			{										// [������ edge���� �����ϰ� �ִ� path�� ��������� ������������ path�� �հ� ���ؼ� shortest�� pick.]
				dist[y] = dist[idx.second] + edge[idx.second][i].second;
				que.push(make_pair(-dist[y], y));				// [first node�� distance ��꿡���� �ʿ� ������, Priority queue�� �ڵ� sorting�� ���� �ùٸ� �켱������ ������ ���ؼ� �ʿ��ϴ�.]	
				
				for (int i = 0; i < restoration.size(); i++)		// Searching the restoration's memory.
				{															// [Path(����)�� ������ �����ϰ� �ִ� restoration�� search.]		
					if (restoration[i].second == y)				// Search the path already exists or not.
					{														// [�������� �����ϱ� ���� ��ΰ� �̹� ����������,
						prev = i;											// �� ª�� ��θ� �߰��߱� ������ update�� �ʿ��ϴ�.]
						break;											// [�̸� ����, index�� ����.]			
					}
					else													// Not exist.
						prev = -1;
				}

				if (prev == -1)											// There is no path to get destination, just store the path.
					restoration.push_back(make_pair(idx.second, y));	// [�������� �����ϱ� ���� path�� ���� ������ ��� ����� ���� ����.]
				else														// There is already path of destination.	
					restoration[prev].first = idx.second;		// [Update�� �ʿ��� ���.]
			}
		}
	}
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	int N, M;
	cin >> N >> M;						// Input of the number of edges and connections.

	for (int i = 0; i < M; i++)
	{
		int a, b, c;							// Temporary variable.
		cin >> a >> b >> c;				// Input of start, end, cost.
		edge[a].push_back(make_pair(b, c));	// Build adjacent list.
		edge[b].push_back(make_pair(a, c));	// Bi-directed graph.	
	}

	Dijkstra(N, M);						// Figure out the method of network resotration.

	cout << restoration.size() << endl;		// Output of the number of MST nodes.
	for (int i = 0; i < restoration.size(); i++)		// Output of each path from start to end.
		cout << restoration[i].first << " " << restoration[i].second << endl;
}