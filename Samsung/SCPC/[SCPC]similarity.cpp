#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
#pragma warning(disable:4996)

using namespace std;

queue<pair<int, int>>que;

int Count(vector<int>a, vector<int>b, int idx, int cnt) 		// Do count the same values in array A and B.
{
	while (a[idx] == b[idx])
	{
		cnt++;			// 동일한 개수이자, 다른 값이 나온 index.
		idx++;
	}

	int k = find(a.begin() + idx, a.end(), b[idx]) - a.begin();
	
	if (k == a.size())
		return cnt;

	for (int p = idx, q = k; p <= q; p++, q--)
		swap(b[p], b[q]);

	for (int p = idx; p < b.size(); p++)
	{
		if (a[p] == b[p])
			cnt++;
	}

	return cnt;
}

int main(int argc, char** argv)
{
	int T, test_case;
	freopen("[scpc_pre2_2019]input_2.txt", "r", stdin);

	cin >> T;
	for (test_case = 0; test_case < T; test_case++)
	{
		int N;				// N = The number of sequences.
		cin >> N;
		vector<int> A(N + 1), B(N + 1);		// A,B = The memory of sequences.

		for (int i = 1; i <= N; i++)
			cin >> A[i];

		for (int j = 1; j <= N; j++)
			cin >> B[j];


		int cnt = 0;
		for (int i = 1; i <= N; i++)
		{
//			int j = find(A.begin() + 1, A.end(), B[i]) - A.begin();
			// 중복된 값을 서치 못함.
			for (int j = 1; j <= N; j++)
			{
				if (B[i] == A[j])
					que.push(make_pair(i, j));
			}

			if (A[i] == B[i])				// 같은 위치에 있는 거 모조리 푸쉬.
				que.push(make_pair(i, ++cnt));
		}

		int Answer = 0;
		if (que.size() == 0)
			Answer = Count(A, B, 1, 0);

		while (!que.empty())
		{
			auto cur = que.front();
			que.pop();

			if (cur.first + 1 >= N)
				continue;
			int idx = cur.first + 1, cnt = cur.second;

			Answer = max(Answer, Count(A, B, idx, cnt));
		}

		cout << "Case #" << test_case + 1 << endl;
		cout << Answer << endl;
	}

	return 0;
}