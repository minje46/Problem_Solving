#include <iostream>
#include <algorithm>
#include <cstring> //memset
using namespace std;

const long long MININF = -2e9;
const int MAX = 1000;

int N, M; //���� ����
int Mars[MAX][MAX];
bool visited[MAX][MAX];
long long cache[3][MAX][MAX]; //���� ������ �Ʒ�

int maxSum(int dir, int col, int row) //����, ����, ����
{
	//������ ���޽�
	if (col == N - 1 && row == M - 1)
		return Mars[col][row];

	long long &result = cache[dir][col][row];
	if (result != MININF)
		return result;

	visited[col][row] = true; //�湮�ߴٰ� ǥ��
	long long candidate1 = MININF, candidate2 = MININF, candidate3 = MININF;
	//����
	if (row - 1 >= 0 && !visited[col][row - 1])
		candidate1 = maxSum(0, col, row - 1);
	//������
	if (row + 1 < M && !visited[col][row + 1])
		candidate2 = maxSum(1, col, row + 1);
	//�Ʒ�
	if (col + 1 < N && !visited[col + 1][row])
		candidate3 = maxSum(2, col + 1, row);

	visited[col][row] = false; //(col, row) �������� ��� ������ ���������� �ִ밡 �� ������ ��� ����Ͽ� �ٽ� �湮���� �ʾҴٰ� ǥ��
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

	//memset MININF �Ұ���
	//memset(cache, MININF, sizeof(cache));
	memset(visited, false, sizeof(visited));
	cout << maxSum(0, 0, 0) << endl;
	return 0;

}