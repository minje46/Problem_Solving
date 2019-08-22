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

		int cur, prev;		// [Current cell �� Previous cell�� ���ؼ� ���ӵǴ� ���� �ľ��ؾ� �Ѵ�.]
		int accumulate[MAX_W], max_tot[MAX_W];
		for (int j = 0; j < W; j++)
		{
			cur = drug[idx] < 0 ? map[idx][j] : drug[idx];	// [(med=-1)�� Not used drug�̹Ƿ�, ���� map[idx][j]���� cur�� �ǰ�, �ƴѰ�� ���� drug�� cur�̵ȴ�.]
			prev = drug[idx - 1] < 0 ? map[idx - 1][j] : drug[idx - 1]; // [Previous ���� ���� drug�� �̿��� �Ǵ��� �� �ִ�.]

			if (cur == prev)		// [Current�� Previous ���� ���ٸ�, ������ ���ӵ� �� +1.]
				accumulate[j] = +prev_acc[j] + 1;		// [������ ���ӵ� ���� prev_acc�� �����ؼ� parameter�� �����ش�.]
			else						// [�ٸ��ٸ�, ���� ���Ȱ��̱� ������ 1�� ����.]
				accumulate[j] = 1;
			// [Drug�� ����ؼ� max_tot�� ����Ǿ����� �ľ�.]				
			max_tot[j] = max(accumulate[j], prev_tot[j]);	// [Drug�� ����ؼ� prev_tot���� �پ�� �� �� ������,
		}																		// �̹� �� ���� dfs�� ���� Ȯ���ϰ� �Ųٷ� ���ƿ��� ���̱⿡ ���X.]	
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
		int accumulate[MAX_W], max_tot[MAX_W];		// The memory of how many cells are continued. [���ӵ� cell�� ���� ����.]
		for (int i = 0; i < W; i++)
			accumulate[i] = max_tot[i] = 1;		// 1 means itself.

		answer = K;		// The maximum number of used is K.
		for (int med = -1; med < DRUG; med++)		// [ -1 : Not use drug.]	
		{
			drug[0] = med;		// [Row�� 1���� search�ϱ� ����, 0��° Row�� �� �� �ִ� [-1,0,1] 3���� ��츦 search.] 
			DFS(1, (med < 0 ? 0 : 1), accumulate, max_tot);		// [Row, Cnt, Accumulate, Max_tot].
		}
		cout << "#" << t << " " << answer << endl;		// Output.
	}
}