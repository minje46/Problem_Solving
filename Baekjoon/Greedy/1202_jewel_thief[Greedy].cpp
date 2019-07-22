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
	{										// [�ѹ� �� ������ �ٽ� �Ⱥ��� ���� key point.]
		while (idx < N && jewel[idx].first <= bag[i])		// [bag�� jewel ��� weight ���� ascending sort �Ǿ� �ֱ� ������, �����Ǵ� ������ �߻����� �ʴ´�.]
			que.push(jewel[idx++].second);					// [Bag�� weight���� ������ ��� pick�Ѵ�.]

		if (!que.empty())				// [Priority queue�� cost �������� sort�Ǳ� ������, K���� ��ŭ queue�� top�� pick�ϸ� �ȴ�.] 
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