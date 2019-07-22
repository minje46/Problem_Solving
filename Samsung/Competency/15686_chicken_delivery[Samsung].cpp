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
{										// [치킨 집을 M개의 순열로 모두 완점탐색하여 비교한다.]
	if (cnt == M)					// M is the maximum number of chicken's shop.
	{
		int total = 0;				// Temporary value to store shortest distance with these permutation of chicken shop.
		int *dist = new int[home.size()];		// Temporary memory to store each distance.
		fill(dist, dist + home.size(), INF);		// Initialize each distance as INFINITY.
		for (int i = 0; i < home.size(); i++)		// [모든 집의 좌표에서,
		{
			for (int j = 0; j < chicken.size(); j++)	// 선택된 치킨 집까지의 거리를 구하는 것.]
				if (visit[j])
					dist[i] = min(dist[i], Distance(home[i], chicken[j]));		// [각 home[i]에서 여러 개의 chicken[j]중 shortest dist만 저장.]

			total += dist[i];		// To store each shortest distance from home[i] to chicken[j].	
		}
		result = min(result, total);		// Compare the shortest distances.	[result에는 앞의 chicken[j] 조합으로 구한 shortest total dist가 저장되어 있다.]
		return;						// Finish this permutation of chicken shop and then make other permutation.
	}									// [현재 조합에서 shortest total dist는 구했으므로, 다른 permutation을 구할 차례.]

	if (idx == chicken.size())	// Base case. [기저사례 : 입력된 문제가 더 이상 줄일 수 없을 만큼 작은 경우.]
		return;

	visit[idx] = true;				// This index of chicken shop is regarded as visited to make permutation.
	DFS(idx + 1, cnt + 1);		// [M개의 Permutation만큼 chicken shop을 만들기 위해, 개수를 증가시키며 DFS.]
	visit[idx] = false;				// [위의 DFS가 끝난 후, 다음 차례의 permutation을 만들기 위해, visit=false로 변경.]
	DFS(idx + 1, cnt );			// [그리고 다음 차례의 치킨 집의 index와 함께 DFS.] [다음 순서의 permutation을 만들기 위함이므로, cnt는 증가X.]
}											

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin >> N >> M;
	for (int i = 1; i <= N; i++)		// i = y좌표.
	{
		for (int j = 1; j <= N; j++)	// j = x좌표.
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
						// [치킨집의 index와 치킨집의 개수를 0으로 시작.] 
	cout << result << endl;		// The minimum distance of total chickenen distance.
}