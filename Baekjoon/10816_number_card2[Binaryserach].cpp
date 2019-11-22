#include<iostream>
#include<map>
#include<vector>

using namespace std;

int N, M;				// N = The number of cards as input.					M = The number of cards possessed.
	// card = The memory of input data.
map<int, int> mp;
vector<pair<int, int>>vc;

int Binary(int value)
{
	int lf = 0, rt = mp.size();
	while (lf < rt)
	{
		int mid = (lf + rt) / 2;

	}
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);	cout.tie(0);

	cin >> N;
	for (int i = 0; i < N; i++)
	{
		int num;
		cin >> num;
		if (mp.find(num) == mp.end())
			mp.insert(make_pair(num, 1));
		else
			mp.find(num)->second += 1;
	}
	for (auto it : mp)
		vc.push_back(make_pair(it.first, it.second));

	cin >> M;
	for (int i = 0; i < M; i++)
	{
		int num;
		cin >> num;
		cout << Binary(num) << " ";
	}
}