#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

// Kruskal�� Prim�� �޸� �������� ������ �̿��ؼ� MST�� ����� ������, Graph�� �����ϴ� ���� �ƴ� �������� ������ ������ �ʿ䰡 �ִ�.
struct Edge			// Memory structure of edge. [���� ������ ���� ����ü.]		
{
	int from;			// Start point.
	int to;			// End point.
	int cost;			// path's cost.
	// To sort this structure. [������ ���� �����ε�.]
	bool operator<(Edge const &e)	
	{
		return cost < e.cost;
	}
};

vector<Edge> edge;		// Memory of edge.	[���� ������ �����ϱ� ���� �޸�.]
int root[10001];				// Memory of root. [Disjoint-set�� ���� node�� root�� �����ϴ� �޸�.] 	
int setSize[10001];			// Memory of root's size. [Disjoint-set�� root-node set�� ���� �����ϴ� �޸�.]
long long answer = 0;		// Minimum cost of spanning tree.

int findRoot(int node)		// To find what the root is.
{
	if (node == root[node])	// If the node is root, it returns itself.
		return node;			// [��� �ڱ� �ڽ��� root�� ���, return.]

	return root[node] = findRoot(root[node]);		// If the node has different root, it should be searched what is the real root. [node�� root�� ��ͷ� �˻�.]
}

void mergeSet(int node1, int node2)		// To merge the sets.
{
	node1 = findRoot(node1);	// Find what is the root of node.
	node2 = findRoot(node2);	// [����� root�� �˻�.]

	if (node1 != node2)		// If they have different root each other, it could be merged in one set.
	{								//[����� ��Ʈ�� ���� �ٸ� ��쿡�� set�� merge�ص� �ȴ�. ���� ��� cycle �߻�.]
		if (setSize[node1] < setSize[node2])		// Compare which one is smaller set.
			swap(node1, node2);		// [Set�� ũ�⸦ ���ؼ�, ���� ������ ��������.]

		root[node2] = node1;			// The node2 is merged in node 1.[node2 ������ node1�� ��������.]
		setSize[node1] += setSize[node2];		//Modify the number of set. [node1�� ���� ũ�� ����.]
		setSize[node2] = 0;			//The node2 set was merged, so it should be empty. [node2�� node1�� ����Ǿ��� ����.]
	}
}

void Kruskal(int V, int E)			// To figure out the MST.
{
	sort(edge.begin(), edge.end());	// At first, the edge's should be sorted. [�������� ������ ������ �켱�� �Ǿ�� �Ѵ�.]

	for (int i = 0; i < V; i++)		// To initialize memory.
	{
		root[i] = i;						// [Root�� �����ϴ� memory�� �ڱ� �ڽ� node�� �ʱ�ȭ.]
		setSize[i] = 1;				// [Node�� set�� ũ�⸦ 1�� �ʱ�ȭ. �ڱ� �ڽŸ� ������ �ֱ� ����.]
	}

	for (int i = 0; i < edge.size(); i++)
	{
		auto e = edge[i];			// The data of edge.
		if (findRoot(e.from) != findRoot(e.to))	// If two edges have different root each other, it is able to be merged in one set.
		{									// [Node�� ���� �ٸ� root�� ������ �־�� merge�� �����ϴ�.]
			answer += e.cost;		// [������ cost�� ����.]
			mergeSet(e.from, e.to);	// It should have merged.
		}
	}
}

int main(void)
{
	ios_base::sync_with_stdio(false);

	int V, E;											// V = The number of vertex.		E = The number of line.
	cin >> V >> E;
	for (int i = 0; i < E; i++)
	{
		int x, y, z;									// Temporary variables to store start node, end node, cost.		
		cin >> x >> y >> z;						// Input of start, end, cost.
		edge.push_back({ x, y, z });
	}

	Kruskal(V, E);									// Figure out minimum spanning tree.	

	cout << answer << endl;					// Out put of minimum spanning tree.
}