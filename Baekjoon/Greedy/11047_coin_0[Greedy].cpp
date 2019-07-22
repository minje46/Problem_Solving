#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

int N, K;						// N = The number of the sort of coins.			K = The total money.
vector<int> vc;			// vc = The memory of which kind of coin the user has.

int Greedy_count()		// To figure out how many times to make a target coin's sum.
{
	int cnt = 0, answer = 0;		// cnt = The count of collections.		answer = The total moeny to compare with target money.

	while (true)				
	{
		if (answer == K)	// Until the total money approaches target money.
			break;

		int tmp = -1;		// The temporary memory to save maximum coin. [Greedy value.]
		for (int i = 0; i < vc.size(); i++)
		{
			if (vc[i] + answer <= K)
				tmp = max(tmp, vc[i]);		// The maximum value as possible as to use. [Greedy selection.]
		}

		if (tmp != -1)
		{
			answer += tmp;		// Reorganize the total money.
			cnt++;					// The counts.
		}
	}

	return cnt;
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin >> N >> K;
	for (int i = 0; i < N; i++)
	{
		int coin;
		cin >> coin;
		vc.push_back(coin);			// The input what the sort of coins are.
	}

	cout << Greedy_count() << endl;
}