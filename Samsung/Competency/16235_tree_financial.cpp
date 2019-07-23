#include<iostream>
#include<algorithm>
#include<vector>

#define MAX 11

using namespace std;

vector<int> map[MAX][MAX];			// The memory of map and stores the age of trees.		[������ ���̸� ��ǥ�� ����.]
int A[MAX][MAX];							// The memory of map's nutrient.	[���� ��ǥ�� ����� ����.]
int New_A[MAX][MAX];					// The memory of new nutrient's data.	[�߰� ���޵Ǵ� ������� ����.]
int dx[8] = { -1, 0, 1, -1, 1, -1, 0, 1 };	// The index of x's movement.
int dy[8] = { -1, -1, -1, 0, 0, 1, 1,1 };		// The index of y's movement.

int main(void)
{
	int N, M, K;
	cin >> N >> M >> K;		// N = The size of map.		M = The number of tree.		K = Years.
	for (int i = 1; i <= N; i++)	// i = x ��ǥ.
	{
		for (int j = 1; j <= N; j++)	// j = y��ǥ.
		{
			cin >> New_A[i][j];	// The value of nutrient of each coordinate.	
			A[i][j] = 5;				// The default nutrient.	
		}
	}

	for (int i = 1; i <= M; i++)
	{
		int x, y, a;					// x = x��ǥ.	y = y��ǥ.	a = ������ ����.
		cin >> x >> y >> a;
		map[x][y].push_back(a);	// [�ش� ��ǥ�� �������� ������ ���ÿ� ������ �� �ֱ� ������ �������� ����.]
	}

	while (K--)						// Until the years goes zero.
	{
		// Spring ~ Summer.
		for (int i = 1; i <= N; i++)		// i = x��ǥ.
		{
			for (int j = 1; j <= N; j++)	// j = y��ǥ.
			{
				sort(map[i][j].begin(), map[i][j].end());	// The youngest tree should take nutrient first.		[� ������ ���� ����.]
				if (!map[i][j].size())		// Size = 0 means there is no tree on this coordinate.		[������ ��ǥ�� �������� �ʴ� ���.]
					continue;

				vector<int> grow;			// To store the tree which gets nutrient successfully.
				vector<int> dead;			// To store the data of dead tree.
				for (int k = 0; k < map[i][j].size(); k++)		// The case of trees exist.
				{
					if (map[i][j][k] <= A[i][j])		// To provide nutrient.
					{								// [���� ����� ��ǥ A�� ������ ���� ��ŭ�� ������� �ִٸ� ���� ����.]
						A[i][j] -= map[i][j][k];		// Decrease the nutrient as tree's age.
						map[i][j][k]++;		// The tree grows.
						grow.push_back(map[i][j][k]);	// Store the data of tree temporarily.
					}
					else							// There is not enough nutrient to provide.	[�������� �����Ҹ�ŭ ������� ���� ���.]
						dead.push_back(map[i][j][k]);
				}
				map[i][j].clear();
				for (int k = 0; k < grow.size(); k++)	// Reorganize the tree's data after summer.
					map[i][j].push_back(grow[k]);

				for (int k = 0; k < dead.size(); k++)	// Summer.
					A[i][j] += dead[k] / 2;				// The dead tree will be nutreint.
			}
		}

		// Falls.
		for (int i = 1; i <= N; i++)		// i = x��ǥ.
		{
			for (int j = 1; j <= N; j++)	// j = y��ǥ.
			{
				if (!map[i][j].size())		// Size = 0 means there is no tree on this coordinate.
					continue;

				for (int k = 0; k < map[i][j].size(); k++)		// The case of trees exist.
				{
					if (map[i][j][k] % 5 == 0)	// The possible case of breeding.	[������ ������ ���.]
					{
						for (int h = 0; h < 8; h++)	// [���� ��ǥ ��.]
						{
							int nx = i + dx[h];
							int ny = j + dy[h];

							if (nx <1 || nx>N || ny<1 || ny>N)
								continue;
							else							// Possible area.		[1~N�� ����� �ʴ� ���� �������� ���� ����.]
								map[nx][ny].push_back(1);

						}
					}
				}
			}
		}

		// Winter.
		for (int i = 1; i <= N; i++)
			for (int j = 1; j <= N; j++)
				A[i][j] += New_A[i][j];		// Add new nutrient.	[����� �߰� ���.]
	}

	int total = 0;
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++)
			total += map[i][j].size();

	cout << total << endl;					// Output of the total number of trees.	[������ �� ����.]
}