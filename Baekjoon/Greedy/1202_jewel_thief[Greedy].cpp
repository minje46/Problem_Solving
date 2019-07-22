#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>

#define MAX 300001

using namespace std;

int N, K;				// N = The number of jerwels.		K = The number of thief's bags.
pair<int, int> jewel[MAX];			// jewel = The memory of each jewel's weight and cost.
int bag[MAX];		// bag =The memory of bags weight.

long long Steal()			// To figure out the most valueable jewel to steal.
{
	long long total = 0;	
	priority_queue<int> que;		// Using for automatic sorting.

	int idx = 0;
	for (int i = 0; i < K; i++)		// Search the whole of bags capacity.
	{										// [한번 본 보석은 다시 안보는 것이 key point.]
		while (idx < N && jewel[idx].first <= bag[i])		// [bag과 jewel 모두 weight 기준 ascending sort 되어 있기 때문에, 누락되는 보석이 발생하지 않는다.]
			que.push(jewel[idx++].second);					// [Bag의 weight보다 낮은건 모두 pick한다.]

		if (!que.empty())				// [Priority queue는 cost 기준으로 sort되기 때문에, K개수 만큼 queue의 top을 pick하면 된다.] 
		{
			total += que.top();
			que.pop();
		}
	}

	return total;
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> N >> K;
	for (int i = 0; i < N; i++)		// Input the Jewel's data.
		cin >> jewel[i].first >> jewel[i].second;
	
	for (int i = 0; i < K; i++)		// Input the thief bag's data.
		cin >> bag[i];

	sort(jewel, jewel + N, less<pair<int, int>>());		// Ascending sort by jewel's weight.
	sort(bag , bag + K, less<int>());						// Ascending sort by weight of bag's capacity.

	cout << Steal() << endl;		// Maximum cost.
}