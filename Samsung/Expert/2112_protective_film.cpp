#include<iostream>
#include<algorithm>
#include<memory.h>
//#pragma warning(disable:4996)

#define MAX_D 14
#define MAX_W 21
#define DRUG 2

using namespace std;

int D, W, K;		// D = The height of map.			W = The width of map.			K = The standards for strength.
int map[MAX_D][MAX_W];		// map = The memory of original input data.
int answer;			// answer = The minimum number of drug used as output.
int drug[MAX_D];					// drug = The memory of which drug was used.

void DFS(int idx, int cnt, int prev_acc[MAX_W], int prev_tot[MAX_W])		// To do exhaustive search the whole of cases.
{
	if (cnt >= answer)	// Base case. [The minimum cnt is valueable.]
		return;

	if (idx == D)		// Base case. [To check it has enough strength or not.]
	{
		for (int i = 0; i < W; i++)		// To check the whole of column has enough strength or not.
		{
			if (prev_tot[i] < K)			// The standard of strength.
				return;
		}
		answer = min(answer, cnt);	// Compare the minimum value.
		return;
	}

	for (int med = -1; med < DRUG; med++)		// [-1 : Not used.]		[0 : A]		[1 : B]
	{
		drug[idx] = med;	// Which drug will use.

		int cur, prev;		// [Current cell 과 Previous cell을 비교해서 연속되는 수를 파악해야 한다.]
		int accumulate[MAX_W], max_tot[MAX_W];
		for (int j = 0; j < W; j++)
		{
			cur = drug[idx] < 0 ? map[idx][j] : drug[idx];	// [(med=-1)은 Not used drug이므로, 현재 map[idx][j]값이 cur이 되고, 아닌경우 사용된 drug가 cur이된다.]
			prev = drug[idx - 1] < 0 ? map[idx - 1][j] : drug[idx - 1]; // [Previous 값은 사용된 drug를 이용해 판단할 수 있다.]

			if (cur == prev)		// [Current와 Previous 값이 같다면, 이전의 연속된 값 +1.]
				accumulate[j] = +prev_acc[j] + 1;		// [이전의 연속된 값은 prev_acc에 저장해서 parameter로 던져준다.]
			else						// [다르다면, 이제 사용된것이기 때문에 1을 저장.]
				accumulate[j] = 1;
			// [Drug를 사용해서 max_tot이 변경되었는지 파악.]				
			max_tot[j] = max(accumulate[j], prev_tot[j]);	// [Drug를 사용해서 prev_tot값이 줄어들 수 도 있지만,
		}																		// 이미 그 전에 dfs를 통해 확인하고 거꾸로 돌아오는 것이기에 상관X.]	
		DFS(idx + 1, cnt + (med < 0 ? 0 : 1), accumulate, max_tot);
	}
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	//	freopen("input.txt", "r", stdin);

	int test_case;
	cin >> test_case;
	for (int t = 1; t <= test_case; t++)
	{	// Initialization.
		memset(map, 0, sizeof(map));
		memset(drug, 0, sizeof(drug));

		cin >> D >> W >> K;
		for (int i = 0; i < D; i++)
		{
			for (int j = 0; j < W; j++)
				cin >> map[i][j];			// Input.
		}

		// Initialization.
		int accumulate[MAX_W], max_tot[MAX_W];		// The memory of how many cells are continued. [연속된 cell의 수를 저장.]
		for (int i = 0; i < W; i++)
			accumulate[i] = max_tot[i] = 1;		// 1 means itself.

		answer = K;		// The maximum number of used is K.
		for (int med = -1; med < DRUG; med++)		// [ -1 : Not use drug.]	
		{
			drug[0] = med;		// [Row를 1부터 search하기 위해, 0번째 Row에 올 수 있는 [-1,0,1] 3가지 경우를 search.] 
			DFS(1, (med < 0 ? 0 : 1), accumulate, max_tot);		// [Row, Cnt, Accumulate, Max_tot].
		}
		cout << "#" << t << " " << answer << endl;		// Output.
	}
}