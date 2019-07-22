#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
#pragma warning(disable:4996)

using namespace std;

int L, S, E;			// L = The total width of map.		S = The start point's height.		E = The end point's height.

int Drone(vector<pair<int, int>>a, vector<pair<int, int>>b) 
{
	int area = 0;
	pair<int, int> dr = { 1, S };		// 드론 위치.(시작점)

	int i = 0, j = 0;
	while (dr.first <= L)
	{
		int w = 0, h = 0, s = 0;

		w = min(a[i].first, b[j].first);
		
		if (S <= a[i].second)
			h = S - b[i].second;
		else
			continue;

		s = w * h;
		dr.first += w;

		area += s;
	}



	return area;
}

int main(int argc, char** argv)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int T, test_case;
	freopen("[scpc_pre2_2019]input_3.txt", "r", stdin);

	cin >> T;
	for (test_case = 0; test_case < T; test_case++)
	{
		cin >> L >> S >> E;

		int A, B;				// A = The number of ceiling data.			B = The number of floor data.
		cin >> A;
		vector<pair<int, int>> up(A);
		for (int i = 0; i < A; i++)
		{
			int a, b;
			cin >> a >> b;
			up[i].first = a;
			up[i].second = b;
		}

		cin >> B;
		vector<pair<int, int>> down(B);
		for (int i = 0; i < B; i++)
		{
			int a, b;
			cin >> a >> b;
			down[i].first = a;
			down[i].second = b;
		}

		int Answer = Drone(up, down);

		cout << "Case #" << test_case + 1 << endl;
		cout << Answer << endl;
	}

	return 0;
}