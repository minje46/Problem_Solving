#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

// Kruskal은 Prim과 달리 간선들의 정보를 이용해서 MST를 만들기 때문에, Graph를 저장하는 것이 아닌 간선들의 정보를 저장할 필요가 있다.
struct Edge			// Memory structure of edge. [간선 정보를 위한 구조체.]		
{
	int from;			// Start point.
	int to;			// End point.
	int cost;			// path's cost.
	// To sort this structure. [정렬을 위한 오버로딩.]
	bool operator<(Edge const &e)	
	{
		return cost < e.cost;
	}
};

vector<Edge> edge;		// Memory of edge.	[간선 정보를 저장하기 위한 메모리.]
int root[10001];				// Memory of root. [Disjoint-set을 위한 node의 root를 저장하는 메모리.] 	
int setSize[10001];			// Memory of root's size. [Disjoint-set의 root-node set의 수를 관리하는 메모리.]
long long answer = 0;		// Minimum cost of spanning tree.

int findRoot(int node)		// To find what the root is.
{
	if (node == root[node])	// If the node is root, it returns itself.
		return node;			// [노드 자기 자신이 root일 경우, return.]

	return root[node] = findRoot(root[node]);		// If the node has different root, it should be searched what is the real root. [node의 root를 재귀로 검색.]
}

void mergeSet(int node1, int node2)		// To merge the sets.
{
	node1 = findRoot(node1);	// Find what is the root of node.
	node2 = findRoot(node2);	// [노드의 root를 검색.]

	if (node1 != node2)		// If they have different root each other, it could be merged in one set.
	{								//[노드의 루트가 서로 다를 경우에는 set을 merge해도 된다. 같은 경우 cycle 발생.]
		if (setSize[node1] < setSize[node2])		// Compare which one is smaller set.
			swap(node1, node2);		// [Set의 크기를 비교해서, 작은 집합이 합쳐진다.]

		root[node2] = node1;			// The node2 is merged in node 1.[node2 집합이 node1에 합쳐진다.]
		setSize[node1] += setSize[node2];		//Modify the number of set. [node1의 집합 크기 수정.]
		setSize[node2] = 0;			//The node2 set was merged, so it should be empty. [node2가 node1에 흡수되었기 때문.]
	}
}

void Kruskal(int V, int E)			// To figure out the MST.
{
	sort(edge.begin(), edge.end());	// At first, the edge's should be sorted. [간선들의 정보가 정렬이 우선시 되어야 한다.]

	for (int i = 0; i < V; i++)		// To initialize memory.
	{
		root[i] = i;						// [Root를 저장하는 memory를 자기 자신 node로 초기화.]
		setSize[i] = 1;				// [Node의 set의 크기를 1로 초기화. 자기 자신만 가지고 있기 때문.]
	}

	for (int i = 0; i < edge.size(); i++)
	{
		auto e = edge[i];			// The data of edge.
		if (findRoot(e.from) != findRoot(e.to))	// If two edges have different root each other, it is able to be merged in one set.
		{									// [Node가 서로 다른 root를 가지고 있어야 merge가 가능하다.]
			answer += e.cost;		// [간선의 cost를 저장.]
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