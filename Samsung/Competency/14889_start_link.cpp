#include<iostream>
#include<algorithm>
#include<vector>
#include<cmath>

#define MAX 21
#define INF 987654321

using namespace std;

int N, mid, answer = INF;			// N = The size of map.	mid = The middle value of N.	answer = The minimum gap between A and B team.
int map[MAX][MAX];		// map = The memory of original map data.
bool visit[MAX];				// visit = The memory of visited or not.

int Gap()		// To calculate the difference value between team A and B.	
{
	vector<int> A, B;		// The memory of each team.

	for (int i = 1; i <= N; i++)
	{
		if (visit[i])		// Team A.
			A.push_back(i);
		else				// Team B.
			B.push_back(i);
	}

	int tot_a = 0, tot_b = 0;		// The memory of total value.
	for (int i = 0; i < A.size(); i++)
	{
		for (int j = 0; j < A.size(); j++)
		{
			if (A[i] == A[j])		// [같은 index는 제외하고,]
				continue;			// [팀의 (i,j) value를 연산한다.]
			tot_a += map[A[i]][A[j]];	// [Loop가 0~Mid까지 두번 돌기 때문에, (i,j)와 (j,i)가 자동으로 계산된다.]	
		}
	}

	for (int i = 0; i < B.size(); i++)
	{
		for (int j = 0; j < B.size(); j++)
		{
			if (B[i] == B[j])
				continue;
			tot_b += map[B[i]][B[j]];
		}
	}

	return abs(tot_a - tot_b);		// Return to absolute valeu. [절댓값으로 반환.]
}

void DFS(int idx, int cnt)		// To check all of combinations using backtracking.
{
	if (cnt == mid)			// Base case.	[nCm을 뜻함.]
	{
		answer = min(answer, Gap());		// To compare the smaller one.
		return;
	}

	if (idx > N)		// Overflow.
		return;

	visit[idx] = true;			// Increase cnt to m. [mid 갯수가 될 때까지 cnt를 증가.]
	DFS(idx + 1, cnt + 1);
	visit[idx] = false;			// Return to last case before DFS.
	DFS(idx + 1, cnt);
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> N;
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
			cin >> map[i][j];				// Map data.
	}
	mid = N / 2;		// Middle value of N.

	DFS(1, 0);			// To do backtracking.

	cout << answer << endl;		// The minimum gap between team A and B.
}