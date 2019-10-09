#include<iostream>
#include<vector>
#include<queue>

#define MAX 100001
#define INF 987654321

using namespace std;

int N, K, M;	// N = The numer of stations.			K = The number of connections in hyper tube.			M = The number of hyper tube.
vector<int> map[MAX+1000];		// map = The memory of input data and dummy node together.
int time[MAX + 1000];					// time = The memory of visited or not and time to get node.
int answer = INF;							// answer = The shortest time to arrive at destination as output.	

void BFS()		// To figure out the way to destination based on bfs.
{
	queue<int>que;
	que.push(1);
	time[1] = 1;		// Departure.
	while (!que.empty())
	{
		auto cur = que.front();
		que.pop();

		if (cur == N)		// Destination.
		{
			answer = time[cur];
			return;
		}

		for (int i = 0; i < map[cur].size(); i++)
		{
			int next = map[cur][i];
			if (time[next] == 0)		// Not visited yet.
			{
				if (next > N)			// Dummy node[Hyper tube.]
					time[next] = time[cur];		// Hyper tube isn't real. So it has same time of node.
				else						// Real node[Station.]
					time[next] = time[cur] + 1;	// Time to arrive at node.
				que.push(next);		
			}
		}
	}
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);	cout.tie(0);

	cin >> N >> K >> M;
	for (int i = 1; i <= M; i++)
	{
		for (int j = 0; j < K; j++)
		{
			int node; 
			cin >> node;
			map[node].push_back(i + N);			// Real station to hyper tube.
			map[i + N].push_back(node);			// Hyper tube has all of vertexes.
		}
	}

	BFS();			// BFS algorithm.

	if (answer == INF)		// Impossible case.
		answer = -1;
	cout << answer << endl;		// Output. 
}