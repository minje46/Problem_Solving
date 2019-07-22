#include<iostream>
#include<algorithm>
#include<vector>
#pragma warning(disable:4996)

using namespace std;

vector<int>vc;						// vc = The memory of values.

int Pivot()
{
	int n = vc.size();				// n = The number of vlaues.
	vector<int>lt(n), rt(n);		// lt = The left memory of base index which store max value from base index.	rt = The right memory of base index which store min value from base index. 
	
	int ma = vc[0];				// ma = The temporary memory for max value.
	for (int i = 0; i < n; i++)
	{
		ma = max(ma, vc[i]);	// [Index기준 left 영역의 max 값 저장.]
		lt[i] = ma;
	}

	int mi = vc[n - 1];			// mi = The temporary memory for min value.
	for (int j = n - 1; j >= 0; j--)
	{
		mi = min(mi, vc[j]);		// [Index기준 right 영역의 min 값 저장.]
		rt[j] = mi;
	}

	int cnt = 0;						// cnt = The memory of counting pivot's condition.
	for (int i = 0; i < n; i++)
	{
		if (vc[i] >= lt[i] && lt[i] <= rt[i])	// Pivot's condition.
			cnt++;
	}
	return cnt;
}

int main(int argc, char** argv)
{
	int T, test_case;

	freopen("[scpc_pre2_2018]input_1.txt", "r", stdin);
	cin >> T;
	for (test_case = 0; test_case < T; test_case++)
	{
		int N;				// N = The number of vlaues.
		cin >> N;

		vc.clear();		// Initiate vector memory to reuse.
		for (int i = 0; i < N; i++)
		{
			int num;
			cin >> num;
			vc.push_back(num);
		}

		int Answer = Pivot();		// Answer = The number of values which satisfy pivot's condition.

		cout << "Case #" << test_case + 1 << endl;
		cout << Answer << endl;
	}

	return 0;
}