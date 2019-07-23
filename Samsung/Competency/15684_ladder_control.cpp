#include<iostream>
#include<algorithm>

#define MAX_N 11
#define MAX_H 33

using namespace std;

bool ladder[MAX_H][MAX_N];	// The memory of ladder's map.
bool flag;		// To judge ladder fabrication is possible or not.	
int result;		// The total number of fabricated ladder.
int N, M, H;	// N = The number of ladder.		M = The number of bridges between ladders.		H = The number of rows.

void DFS(int y, int cnt)
{
	if (flag)		// The ladder can be controlled. 
		return;

	if (result == cnt)		// The case that fabricated ladder and connected bridges are same.
	{				// [�����Ϸ��� ��ٸ� ������ ����� ��ٸ��� ������ ���� ���, (i���, i����) �������� check.]	
		bool possible = true;
		for (int i = 1; i <= N; i++)	// Each ladder's number.	[��ٸ��� ���ʴ�� Ȯ��.]
		{
			int row = i;		// The destination. [������ �񱳸� ���� ����.]
			for (int j = 1; j <= H; j++)	// To chase ladder. [��ٸ��� ���ʴ�� �׷������� ����.]
			{
				if (ladder[j][row])		// Right directed bridge.
					row++;	// [���������� ����� �ٸ��� ���� �̵�.]
				else if (row > 1 && ladder[j][row - 1])	// Left directed bridge.
					row--;	// [�������� ����� �ٸ��� ���� �̵�.]
			}

			if (i != row)		// If the destination is different with departure, it's wrong.
			{					// [�����, ������ �ٸ� ���.]
				possible = false;
				break;
			}
		}
		if (possible)		// All ladders are having same destination with their own departure.
			flag = true;		// [��� ��ٸ��� �����, �������� ���� ���.] 
		return;
	}

	for (int i = y; i <= H; i++)		// i = y��ǥ.
	{
		for (int j = 1; j < N; j++)	// j = x��ǥ.
		{
			if (!ladder[i][j - 1] && !ladder[i][j] && !ladder[i][j + 1])		// The conditions to connect bridge.
			{								// [�����ϰų�, �̿��ؼ� �ٸ��� ������ �� ���� ����.]
				ladder[i][j] = true;
				DFS(i, cnt + 1);
				ladder[i][j] = false;
			}
		}
	}
	return;
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin >> N >> M >> H;
	for (int i = 0; i < M; i++)		// Organize the bridges between ladders.
	{
		int y, x;
		cin >> y >> x;
		ladder[y][x] = true;			// It means there is bridge from (y,x) to (y,x+1).
	}

	for (int i = 0; i <= 3; i++)
	{
		result = i;
		DFS(0, 0);	// start coordinates, count of fabrication.
		if (flag)
		{
			cout << result << endl;
			return 0;
		}
	}
	cout << -1 << endl;
}