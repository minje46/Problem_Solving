#include<iostream>
#include<map>
#include<vector>

using namespace std;

int N, M;							// N = The number of cards as input.					M = The number of cards possessed.
map<int, int> mp;			// mp = The memory of input data. [Card, Count]
vector<pair<int, int>>vc;	// vc = The memory of number cards.

int Binary(int value)			// To figure out the number exists or not based on binary search.
{
	int lf = 0, rt = mp.size()-1;	// Left and Right index.
	while (lf <= rt)
	{
		int mid = (lf + rt) / 2;

		if (value == vc[mid].first)		// Base case.
			return vc[mid].second;	// Find the value.

		if (lf >= rt)			// Base case.
			return 0;			// Overflow.

		if (vc[mid].first > value)		// Go left.
			rt = mid;
		else					// Go right.
			lf = mid + 1;
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
		cin >> num;										// Input.
		if (mp.find(num) == mp.end())				// New number card.
			mp.insert(make_pair(num, 1));		
		else													// Number is already existed.
			mp.find(num)->second += 1;			// Increase the count.
	}
	for (auto it : mp)										// Copy the data in vector data structure.
		vc.push_back(make_pair(it.first, it.second));		// To search easily with index.

	cin >> M;
	for (int i = 0; i < M; i++)
	{
		int num;
		cin >> num;
		cout << Binary(num) << " ";						// Output.	
	}
}