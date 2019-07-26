#include<iostream>
#include<algorithm>
#include<vector>
#include<memory.h>
//#pragma warning(disable:4996)

#define MAX 21

using namespace std;

int N;										// N = The size of map.			
int map[MAX][MAX];				// map = The memory of original map.
bool visit[MAX][MAX];				// visit = The memory of visited or not.
int dy[4] = { -1,-1,1,1 };			// Left+Up,		Rigt+UP.
int dx[4] = { -1,1,-1,1 };			// Left+Down,		Right+Down.
pair<int, int> start;					// start = The memory of start location.
vector<int> dessert;					// dessert = The memory of dessert they visited.
int answer = -1;						// answer = The maximum output of distance.
bool flag = false;						// flag = The memory of distinction.
bool dir[4] = { false, };			// dir = The memory of direction could move or not.

void DFS(int y, int x, int idx)		// To search every way to visit.
{
	if (y == start.first && x == start.second && dessert.size() >= 4)			// If the cycle exists.
	{
		flag = true;						// Flag is the marker of cycle's existance.
		int cnt = dessert.size();	// The distance of visited cafe.	
		answer = max(answer, cnt);		// The longest distance should be answer.
		return;
	}

	visit[y][x] = true;				// Visit check.	
	dessert.push_back(map[y][x]);		// To distinguish duplicated cafe or not.

	for (int i = 0; i < 4; i++)
	{
		int ny = y + dy[i];
		int nx = x + dx[i];

		if (y == start.first && x == start.second)		// On start point, the right and down position makes the whole of cases as well.	
		{		
			if (i != 3)		// [Start point���� ������ �ϴܸ� search�ص� ��� ��츦 üũ�� �� �ֱ� ������, ������ �ϴܸ� search�Ѵ�.]
				continue;
		}
		
		if (i == idx)			// If the direction is gonnabe same direction which was directed, it could go.
			dir[idx] = false;		// [������ �������δ� ������ ������ �� �ֱ� ������, ���� ó��.]

		if (ny < 1 || ny > N || nx < 1 || nx > N || dir[i])			// Overflow.
			continue;

		if (ny == start.first && nx == start.second)		// [Start point�� �ǵ��� ���� ��, cycle�� ������ ������, �ƴϸ� �ߺ��� ���������� �Ǵ��ϱ� ����.]
		{
			if (dessert.size() >= 4)		// [Cycle�� �������� ���, ���� ���� ������ �簢���� �̷���� ���̹Ƿ�, size()�� ���� �Ǵ�.]
				DFS(ny, nx, i);
		}

		if (!visit[ny][nx] && find(dessert.begin(), dessert.end(), map[ny][nx]) == dessert.end())		// [�ߺ��� cafe�湮 ���ο� �ִ��� �Ǵ�.]
		{
			dir[i] = true;			// [�ش� direction���� �̵����� ���, ���� �̵����� ���� direction���θ� �̵��� �����ϴ�.]
			DFS(ny, nx, i);
			dir[i] = false;			// Backtracking.
			visit[ny][nx] = false;		// Backtracking. [DFS�� Ȯ���ϰ� �ǵ��ƿ��鼭, �ٽ� ���󺹱� �����ִ� �۾�.]
			dessert.pop_back();
		}
	}
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	//freopen("input.txt", "r", stdin);
	
	int test_case;
	cin >> test_case;
	for (int t = 1; t <= test_case; t++)
	{	// Initialize
		memset(map, 0, sizeof(map));
		flag = false;					

		cin >> N;
		for (int i = 1; i <= N; i++)
		{
			for (int j = 1; j <= N; j++)
				cin >> map[i][j];			// Original map.
		}

		answer = -1;
		for (int i = 1; i <= N - 1; i++)
		{
			for (int j = 2; j <= N - 1; j++)
			{
				memset(visit, false, sizeof(visit));
				dessert.clear();
				start.first = i;
				start.second = j;
				DFS(i, j, 0);			// To figure out search the whole of cases.
			}
		}

		if(flag)		// If there is the way to visit.
			cout << "#" << t << " " << answer << endl;
		else			// No way.
			cout << "#" << t << " " << -1 << endl;
	}

}