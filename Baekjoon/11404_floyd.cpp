#include<iostream>
#include<vector>
#include<algorithm>

#define INF 987654321
#define MAX 102

using namespace std;

int dist[MAX][MAX];							// The memory of distance.
bool cycle = false;								// To figure out whether there is negative cycle or not.

void Floyd_warshall(int N)						// To figure out the shortest path.
{
	for (int k = 1; k <= N; k++)				// The stop over vertex.	[�����ϴ� ���� �ǹ�.]
		for (int i = 1; i <= N; i++)				// Departurevertex.	[��� ���� �ǹ�.]
			for (int j = 1; j <= N; j++)			// Destination vertex.	[���� ���� �ǹ�.]
				if (dist[i][j] > dist[i][k] + dist[k][j])		// Compare the path.
					dist[i][j] = dist[i][k] + dist[k][j];		// [i~j���� �����ϴ� path�� i~k�� �����ؼ� k~j���� �����ϴ� path�� ���� ��.]
}

int main(void)
{
	int N, M;
	cin >> N >> M;					// N = The number of vertex.		M = The number of edges.

	for (int i = 1; i <= N; i++)		// Initialize each distance as INFINITY.
		for (int j = 1; j <= N; j++)
			dist[i][j] = INF;

	for (int i = 0; i < M; i++)		// Input of edges.
	{
		int a, b, c;
		cin >> a >> b >> c;
		if(dist[a][b] > c)
			dist[a][b] = c;			// Organize the graph with edges.
	}

	Floyd_warshall(N);

	for (int i = 1; i <= N; i++)		
	{
		for (int j = 1; j <= N; j++)
		{
			if (i == j || dist[i][j] == INF)
				cout << 0 << " ";
			else
				cout << dist[i][j] << " ";		// Shortest path.
		}
		cout << endl;
	}
}