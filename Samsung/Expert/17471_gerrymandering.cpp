#include<iostream>
#include<algorithm>
#include<memory.h>
#include<vector>
#include<queue>

#define MAX 11
#define INF 987654321

using namespace std;

int N, answer = INF;				// N = The number of distinctions.				answer = The minimum difference between two groups.
bool map[MAX][MAX];		// map = The memory of graph connection.	
int vote[MAX];					// vote = The memory of each distinction's votes.
bool order[MAX];				// order = The memory of order to do permutation.
bool visit[MAX];					// visit = The memory of visited or not.

bool BFS(int dpt, int dst, vector<int> vc)		// To figure out whether it is possible to arrive at destination.
{
	queue<int> que;
	que.push(dpt);
	while (!que.empty())
	{
		auto cur = que.front();
		que.pop();

		if (cur == dst)			// Arrive at destination.
			return true;
		
		visit[cur] = true;
		for (int i = 1; i < MAX; i++)
		{
			if (!map[cur][i])		// Not connected.
				continue;

			if (!visit[i] && find(vc.begin(), vc.end(), i) != vc.end())		// Connected + Not visited yet + Included in same group.
				que.push(i);
		}
	}
	return false;
}

void Simulation()			// To do simulation.
{
	do
	{
		vector<int> A, B;			// A, B = Two parts of separated group.
		for (int i = 1; i <= N; i++)
		{
			if (order[i])				// A group.
				A.push_back(i);
			else						// B group.
				B.push_back(i);
		}

		bool connect = true;		// To check all graphs are connected or not.
		if (A.size() > 1)				// If it has only one node, it donesn't need to take care.
		{
			for (int i = 0; i < A.size(); i++)		// Start node.
			{	
				connect = true;
				for (int j = i + 1; j < A.size(); j++)		// End node.
				{
					if (map[A[i]][A[j]])		// Direct connected.
						continue;

					memset(visit, false, sizeof(visit));		// Initialization.
					visit[A[i]] = true;				
					if (!BFS(A[i], A[j], A))		// Indirect connection.	
					{
						connect = false;			// Not connected.
						break;
					}
				}
				if (!connect)		// To get out this loop.
					break;
			}
		}
		if (!connect)		// All graphs aren't connected.
			continue;

		connect = true;	// To check all graphs are connected or not.
		if (B.size() > 1)	// If it has only one node, it donesn't need to take care.
		{
			for (int i = 0; i <B.size(); i++)		// Start node.
			{
				connect = true;
				for (int j = i + 1; j < B.size(); j++)		// End node.
				{
					if (map[B[i]][B[j]])		// Direct connected.
						continue;

					memset(visit, false, sizeof(visit));		// Initialization.
					visit[B[i]] = true;
					if (!BFS(B[i], B[j], B))		// Indirect connection.	
					{
						connect = false;			// Not connected.
						break;
					}
				}
				if (!connect)	// To get out this loop.
					break;
			}
		}
		if (!connect)			// All graphs aren't connected.
			continue;

		int tot_a = 0, tot_b = 0;		
		for (int i = 0; i < A.size(); i++)
			tot_a += vote[A[i]];				// The total number of A group's votes.
		for (int i = 0; i < B.size(); i++)
			tot_b += vote[B[i]];				// The total number of B group's votes.

		answer = min(answer, abs(tot_a - tot_b));		// Compare minimum difference between A and B groups.
	} while (next_permutation(order + 1, order + N+1));
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	memset(map, false, sizeof(map));

	cin >> N;							// The number of distinctions.
	for (int i = 1; i <= N; i++)
		cin >> vote[i];				// The number of votes in each distinction.
	for (int i = 1; i <= N; i++)		// [START Node.]
	{
		int num;
		cin >> num;					// The number of connected to others.
		for (int j = 0; j < num; j++)
		{
			int dst;
			cin >> dst;					// [END Node.]
			map[i][dst] = true;
			map[dst][i] = true;
		}
	}

	for (int i = 1; i < N; i++)		// From 1 to (N-1), check all of combination cases.
	{
		memset(order, false, sizeof(order));		// Initialization.
		for (int j = N; j > N - i; j--)
			order[j] = true;			// Check the base form of combination case.
		
		Simulation();					// Simulation.
	}

	if (answer == INF)				// Impossible case.
		answer = -1;
	cout << answer << endl;		// Output.
}