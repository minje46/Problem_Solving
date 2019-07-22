#include<iostream>
#include<algorithm>
#include<vector>
#include<string.h>
#include<memory.h>
#include<math.h>

#define MAX 51
#define INF 987654321

using namespace std;

vector<pair<int, int>> home;				// The memory of home's coordinate.
vector<pair<int, int>> chicken;			// The memory of chicken shop's coordinate.
bool visit[MAX];								// The memory of visit whether chicken shop was visited or not.
int N, M, result = INF;						// N = The size of map.		M = The maximum's number of chicken shop.		result = The answer.

int Distance(pair<int, int>a, pair<int, int>b)		// To figure out distance between A and B.
{
	return abs(a.first - b.first) + abs(a.second - b.second);
}

void DFS(int idx, int cnt)		// To do exhaustive search all of chicken's shop with making M's permutation.
{										// [ġŲ ���� M���� ������ ��� ����Ž���Ͽ� ���Ѵ�.]
	if (cnt == M)					// M is the maximum number of chicken's shop.
	{
		int total = 0;				// Temporary value to store shortest distance with these permutation of chicken shop.
		int *dist = new int[home.size()];		// Temporary memory to store each distance.
		fill(dist, dist + home.size(), INF);		// Initialize each distance as INFINITY.
		for (int i = 0; i < home.size(); i++)		// [��� ���� ��ǥ����,
		{
			for (int j = 0; j < chicken.size(); j++)	// ���õ� ġŲ �������� �Ÿ��� ���ϴ� ��.]
				if (visit[j])
					dist[i] = min(dist[i], Distance(home[i], chicken[j]));		// [�� home[i]���� ���� ���� chicken[j]�� shortest dist�� ����.]

			total += dist[i];		// To store each shortest distance from home[i] to chicken[j].	
		}
		result = min(result, total);		// Compare the shortest distances.	[result���� ���� chicken[j] �������� ���� shortest total dist�� ����Ǿ� �ִ�.]
		return;						// Finish this permutation of chicken shop and then make other permutation.
	}									// [���� ���տ��� shortest total dist�� �������Ƿ�, �ٸ� permutation�� ���� ����.]

	if (idx == chicken.size())	// Base case. [������� : �Էµ� ������ �� �̻� ���� �� ���� ��ŭ ���� ���.]
		return;

	visit[idx] = true;				// This index of chicken shop is regarded as visited to make permutation.
	DFS(idx + 1, cnt + 1);		// [M���� Permutation��ŭ chicken shop�� ����� ����, ������ ������Ű�� DFS.]
	visit[idx] = false;				// [���� DFS�� ���� ��, ���� ������ permutation�� ����� ����, visit=false�� ����.]
	DFS(idx + 1, cnt );			// [�׸��� ���� ������ ġŲ ���� index�� �Բ� DFS.] [���� ������ permutation�� ����� �����̹Ƿ�, cnt�� ����X.]
}											

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin >> N >> M;
	for (int i = 1; i <= N; i++)		// i = y��ǥ.
	{
		for (int j = 1; j <= N; j++)	// j = x��ǥ.
		{
			int val;				
			cin >> val;					// Input of map.
			if (val == 1)				// Home. 
				home.push_back({ i, j });		// The coordinate of home.
			else if (val == 2)			// chickenen shop.
				chicken.push_back({ i,j });	// The coordinate of chicken shop.	
		}
	}

	DFS(0, 0);		// Start exhaustive search with chicken shop's index as zero and count of shop as zero.
						// [ġŲ���� index�� ġŲ���� ������ 0���� ����.] 
	cout << result << endl;		// The minimum distance of total chickenen distance.
}