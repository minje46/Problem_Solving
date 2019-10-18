#include <iostream>
#include <algorithm>
#include <cstring> //memset
using namespace std;

const long long MININF = -2e9;
const int MAX = 1000;

int N, M; //세로 가로
int Mars[MAX][MAX];
bool visited[MAX][MAX];
long long cache[3][MAX][MAX]; //왼쪽 오른쪽 아래

int maxSum(int dir, int col, int row) //방향, 세로, 가로
{
	//목적지 도달시
	if (col == N - 1 && row == M - 1)
		return Mars[col][row];

	long long &result = cache[dir][col][row];
	if (result != MININF)
		return result;

	visited[col][row] = true; //방문했다고 표시
	long long candidate1 = MININF, candidate2 = MININF, candidate3 = MININF;
	//왼쪽
	if (row - 1 >= 0 && !visited[col][row - 1])
		candidate1 = maxSum(0, col, row - 1);
	//오른쪽
	if (row + 1 < M && !visited[col][row + 1])
		candidate2 = maxSum(1, col, row + 1);
	//아래
	if (col + 1 < N && !visited[col + 1][row])
		candidate3 = maxSum(2, col + 1, row);

	visited[col][row] = false; //(col, row) 기준으로 모든 방향을 가봤음에도 최대가 안 나오는 경우 고려하여 다시 방문하지 않았다고 표시
	return result = Mars[col][row] + max(max(candidate1, candidate2), candidate3);
}

int main(void)
{
	cin >> N >> M;

	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
		{
			cin >> Mars[i][j];
			cache[0][i][j] = cache[1][i][j] = cache[2][i][j] = MININF;
		}

	//memset MININF 불가능
	//memset(cache, MININF, sizeof(cache));
	memset(visited, false, sizeof(visited));
	cout << maxSum(0, 0, 0) << endl;
	return 0;

}