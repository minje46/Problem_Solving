#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

int N, M;				// N = The number of cards as input.					M = The number of cards possessed.
vector<int>vc;		// vc = The memory of number cards.

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);	cout.tie(0);

	cin >> N;
	for (int i = 0; i < N; i++)
	{
		int num;
		cin >> num;							// Input.
		vc.push_back(num);
	}
	sort(vc.begin(), vc.end());			// Ascending sort for binary search.
	cin >> M;
	for (int i = 0; i < M; i++)
	{
		int num;
		cin >> num;
		int answer = upper_bound(vc.begin(), vc.end(), num) - lower_bound(vc.begin(), vc.end(), num);
		cout << answer << " ";				// Output.	
	}
}