#include<iostream>
#include<algorithm>
#include<vector>

#define MAX 11

using namespace std;

vector<int> map[MAX][MAX];			// The memory of map and stores the age of trees.		[나무의 나이를 좌표에 저장.]
int A[MAX][MAX];							// The memory of map's nutrient.	[현재 좌표의 영양분 관리.]
int New_A[MAX][MAX];					// The memory of new nutrient's data.	[추가 공급되는 영양분을 저장.]
int dx[8] = { -1, 0, 1, -1, 1, -1, 0, 1 };	// The index of x's movement.
int dy[8] = { -1, -1, -1, 0, 0, 1, 1,1 };		// The index of y's movement.

int main(void)
{
	int N, M, K;
	cin >> N >> M >> K;		// N = The size of map.		M = The number of tree.		K = Years.
	for (int i = 1; i <= N; i++)	// i = x 좌표.
	{
		for (int j = 1; j <= N; j++)	// j = y좌표.
		{
			cin >> New_A[i][j];	// The value of nutrient of each coordinate.	
			A[i][j] = 5;				// The default nutrient.	
		}
	}

	for (int i = 1; i <= M; i++)
	{
		int x, y, a;					// x = x좌표.	y = y좌표.	a = 나무의 나이.
		cin >> x >> y >> a;
		map[x][y].push_back(a);	// [해당 좌표에 여러개의 나무가 동시에 존재할 수 있기 때문에 동적으로 관리.]
	}

	while (K--)						// Until the years goes zero.
	{
		// Spring ~ Summer.
		for (int i = 1; i <= N; i++)		// i = x좌표.
		{
			for (int j = 1; j <= N; j++)	// j = y좌표.
			{
				sort(map[i][j].begin(), map[i][j].end());	// The youngest tree should take nutrient first.		[어린 나무가 먼저 공급.]
				if (!map[i][j].size())		// Size = 0 means there is no tree on this coordinate.		[나무가 좌표에 존재하지 않는 경우.]
					continue;

				vector<int> grow;			// To store the tree which gets nutrient successfully.
				vector<int> dead;			// To store the data of dead tree.
				for (int k = 0; k < map[i][j].size(); k++)		// The case of trees exist.
				{
					if (map[i][j][k] <= A[i][j])		// To provide nutrient.
					{								// [현재 영양분 좌표 A에 나무의 나이 만큼의 영양분이 있다면 공급 가능.]
						A[i][j] -= map[i][j][k];		// Decrease the nutrient as tree's age.
						map[i][j][k]++;		// The tree grows.
						grow.push_back(map[i][j][k]);	// Store the data of tree temporarily.
					}
					else							// There is not enough nutrient to provide.	[나무에게 제공할만큼 영양분이 없는 경우.]
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
		for (int i = 1; i <= N; i++)		// i = x좌표.
		{
			for (int j = 1; j <= N; j++)	// j = y좌표.
			{
				if (!map[i][j].size())		// Size = 0 means there is no tree on this coordinate.
					continue;

				for (int k = 0; k < map[i][j].size(); k++)		// The case of trees exist.
				{
					if (map[i][j][k] % 5 == 0)	// The possible case of breeding.	[번식이 가능한 경우.]
					{
						for (int h = 0; h < 8; h++)	// [주위 좌표 비교.]
						{
							int nx = i + dx[h];
							int ny = j + dy[h];

							if (nx <1 || nx>N || ny<1 || ny>N)
								continue;
							else							// Possible area.		[1~N을 벗어나지 않는 범위 내에서만 번식 가능.]
								map[nx][ny].push_back(1);

						}
					}
				}
			}
		}

		// Winter.
		for (int i = 1; i <= N; i++)
			for (int j = 1; j <= N; j++)
				A[i][j] += New_A[i][j];		// Add new nutrient.	[영양분 추가 배급.]
	}

	int total = 0;
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++)
			total += map[i][j].size();

	cout << total << endl;					// Output of the total number of trees.	[나무의 총 개수.]
}