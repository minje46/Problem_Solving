#include<iostream>
#include<algorithm>
#include<vector>
#include<memory.h>
//#pragma warning(disable:4996)

#define MAX 13

using namespace std;

int N;												// N = The size of map.
int map[MAX][MAX] = { 0, };			// map = The memory of initial map.
bool visit[MAX][MAX] = { false, };	// visit = The memory of visited or not.
vector<pair<int, int>> core;				// core = The memory of core's location.
pair<int, int>answer;						// answer = The output memory.

void Check(int code, int idx, bool flag)		// Organize visit memory as flag(true or false).
{
	switch (code)			// Based on code number. It means Up, Down, Left, Right.
	{
	case 0:			// Up.
		for (int i = core[idx].first - 1; i >= 1; i--)
			visit[i][core[idx].second] = flag;
		break;

	case 1:			// Down.
		for (int i = core[idx].first + 1; i <= N; i++)
			visit[i][core[idx].second] = flag;
		break;

	case 2:			// Left.
		for (int i = core[idx].second - 1; i >= 1; i--)
			visit[core[idx].first][i] = flag;
		break;

	case 3:			// Right.
		for (int i = core[idx].second + 1; i <= N; i++)
			visit[core[idx].first][i] = flag;
		break;

	default:
		break;
	}
}

bool promising(int code, int idx)		// To figure out it is possible to connect cable from current processor.
{
	switch (code)				// Based on code number. It means Up, Down, Left, Right.
	{
	case 0:				// Up.
		for (int i = core[idx].first - 1; i >= 1; i--)
			if (map[i][core[idx].second] == 1 || visit[i][core[idx].second])
				return false;
		break;

	case 1:				// Down.
		for (int i = core[idx].first+1; i <= N; i++)
			if (map[i][core[idx].second] == 1 || visit[i][core[idx].second])
				return false;
		break;

	case 2:				// Left.
		for (int i = core[idx].second - 1; i >= 1; i--)
			if (map[core[idx].first][i] == 1 || visit[core[idx].first][i])
				return false;
		break;

	case 3:				// Right.
		for (int i = core[idx].second+1; i <= N; i++)
			if (map[core[idx].first][i] == 1 || visit[core[idx].first][i])
				return false;
		break;

	default:
		break;
	}

	return true;
}

void DFS(int idx, int cnt, int len)
{
	if (idx == core.size())		// Base case.	[From first processor to last processor.]
	{
		if (cnt > answer.first)	// The maximum number of processor is main factor for comparison.
		{
			answer.first = cnt;
			answer.second = len;
		}
		else if (cnt == answer.first)		// Then, the minimum length of cable is second factor.
		{
			if (answer.second > len)
				answer.second = len;
		}
		return;
	}

	int no = 0;			// no = It is for passing current processro which couldn't connect cable.
	for (int i = 0; i < 4; i++)		// 0 = Up.		1 = Down.			2 = Left.				3 = Right.
	{
		if (i == 0)		// Up.
		{
			if (promising(i, idx))			// Possible to connect cable.
			{
				Check(i, idx, true);		// Organize as true. 	
				int tmp = core[idx].first - 1;		// The length of cable from current processor's location.
				DFS(idx + 1, cnt + 1, len + tmp);
				Check(i, idx, false);		// Reorganize as false.(Original one.)
			}
			else
				no++;
		}

		else if (i == 1)		// Down.
		{
			if (promising(i, idx))		// Possible to connect cable.
			{
				Check(i, idx, true);
				int tmp = N - core[idx].first;
				DFS(idx + 1, cnt + 1, len + tmp);
				Check(i, idx, false);
			}
			else
				no++;
		}

		else if (i == 2)		// Left.
		{
			if (promising(i, idx))		// Possible to connect cable.
			{
				Check(i, idx, true);
				int tmp = core[idx].second - 1;
				DFS(idx + 1, cnt + 1, len + tmp);
				Check(i, idx, false);
			}
			else
				no++;
		}

		else		// Right.
		{
			if (promising(i, idx))		// Possible to connect cable.
			{
				Check(i, idx, true);
				int tmp = N - core[idx].second;
				DFS(idx + 1, cnt + 1, len + tmp);
				Check(i, idx, false);
			}
			else
				no++;
		}
	}
	if (no == 4)			// [Processor가 연결이 불가능 할 경우, 다음 processor를 비교.] 
		DFS(idx + 1, cnt, len);			// [항상 모든 processor가 연결되어야 하는 것은 X.]
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	//freopen("input.txt", "r", stdin);

	int test_case;
	cin >> test_case;
	for (int t = 1; t <= test_case; t++)
	{	// Initialize.
		answer.first = -1;
		answer.second = 987654321;
		memset(visit, false, sizeof(visit));
		memset(map, 0, sizeof(map));
		core.clear();

		cin >> N;			// The size of map.
		for (int i = 1; i <= N; i++)
		{
			for (int j = 1; j <= N; j++)
			{
				cin >> map[i][j];
				if (map[i][j] == 1)		// The processor exists.
				{
					if (i == 1 || i == N || j == 1 || j == N)		// It doesn't consider which is located on outline.
						continue;
					core.push_back(make_pair(i, j));				// Core's location.
					visit[i][j] = true;		// The processor's location makes visit = true.
				}
			}
		}

		DFS(0, 0, 0);		// (index, count, length)		

		cout << "#" << t << " " << answer.second << endl;			// The output of minimum length.
	}
}