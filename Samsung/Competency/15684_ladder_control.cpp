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
	{				// [조작하려는 사다리 개수와 연결된 사다리의 개수가 같은 경우, (i출발, i도착) 가능한지 check.]	
		bool possible = true;
		for (int i = 1; i <= N; i++)	// Each ladder's number.	[사다리를 차례대로 확인.]
		{
			int row = i;		// The destination. [도착점 비교를 위한 저장.]
			for (int j = 1; j <= H; j++)	// To chase ladder. [사다리를 차례대로 그려나가는 과정.]
			{
				if (ladder[j][row])		// Right directed bridge.
					row++;	// [오른쪽으로 연결된 다리를 통해 이동.]
				else if (row > 1 && ladder[j][row - 1])	// Left directed bridge.
					row--;	// [왼쪽으로 연결된 다리를 통해 이동.]
			}

			if (i != row)		// If the destination is different with departure, it's wrong.
			{					// [출발지, 도착지 다른 경우.]
				possible = false;
				break;
			}
		}
		if (possible)		// All ladders are having same destination with their own departure.
			flag = true;		// [모든 사다리의 출발지, 도착지가 같은 경우.] 
		return;
	}

	for (int i = y; i <= H; i++)		// i = y좌표.
	{
		for (int j = 1; j < N; j++)	// j = x좌표.
		{
			if (!ladder[i][j - 1] && !ladder[i][j] && !ladder[i][j + 1])		// The conditions to connect bridge.
			{								// [연속하거나, 이웃해서 다리를 연결할 수 없는 조건.]
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