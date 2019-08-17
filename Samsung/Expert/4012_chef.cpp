#include<iostream>
#include<algorithm>
#include<memory.h>
#include<vector>
//#pragma warning(disable:4996)

#define MAX 17
#define INF 987654321

using namespace std;

int N;			// N = The number of food reserves.
int map[MAX][MAX];		// map = The memory of original input.
bool visit[MAX];				// visit = The memory of visited or not.
int answer = INF;				// answer = The minimum gap between foods as output.
	
int Cook()		// To figure out the value of food A and B.
{
	vector<int>A, B;		// The memory of food A and B's reserves.
	for (int i = 0; i < N; i++)
	{
		if (visit[i])			// Food A's reserves.
			A.push_back(i);
		else					// Food B's reserves.
			B.push_back(i);
	}

	int tot_A = 0, tot_B = 0;		// The memory of food A and B's total value.
	for (int i = 0; i < A.size(); i++)	
	{		
		for (int j = 0; j < A.size(); j++)	
		{
			if (i == j)			// Except same reserves.
				continue;
			tot_A += map[A[i]][A[j]];		// Food A.
		}
	}

	for (int i = 0; i < B.size(); i++)
	{
		for (int j = 0; j < B.size(); j++)
		{
			if (i == j)			// Except same reserves.
				continue;
			tot_B += map[B[i]][B[j]];		// Food B.
		}
	}
	return abs(tot_A - tot_B);		// The gap of food A and B.
}

void DFS(int idx, int cnt)		// To do exhaustive search as combination set.
{
	if (cnt >= (N / 2))			// Base case.
	{
		answer = min(answer, Cook());		// Compare the value.
		return;
	}

	if (idx > N)		// Overflow.
		return;

	visit[idx] = true;
	DFS(idx + 1, cnt + 1);
	visit[idx] = false;
	DFS(idx + 1, cnt);
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	//freopen("input.txt", "r", stdin);

	int test_case;
	cin >> test_case;
	for (int t = 1; t <= test_case; t++)
	{	// Initialization.
		memset(map, 0, sizeof(map));
		memset(visit, false, sizeof(visit));

		cin >> N;
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
				cin >> map[i][j];			// Input.
		}

		answer = INF;
		DFS(0, 0);			// To do exhaustive search.

		cout << "#" << t << " " << answer << endl;		// Output.
	}
}