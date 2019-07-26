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
			if (i != 3)		// [Start point에서 오른쪽 하단만 search해도 모든 경우를 체크할 수 있기 때문에, 오른쪽 하단만 search한다.]
				continue;
		}
		
		if (i == idx)			// If the direction is gonnabe same direction which was directed, it could go.
			dir[idx] = false;		// [동일한 방향으로는 언제든 움직일 수 있기 때문에, 예외 처리.]

		if (ny < 1 || ny > N || nx < 1 || nx > N || dir[i])			// Overflow.
			continue;

		if (ny == start.first && nx == start.second)		// [Start point로 되돌아 왔을 때, cycle을 형성한 것인지, 아니면 중복된 움직임인지 판단하기 위함.]
		{
			if (dessert.size() >= 4)		// [Cycle을 형성했을 경우, 가장 작은 단위인 사각형을 이루었을 것이므로, size()를 통해 판단.]
				DFS(ny, nx, i);
		}

		if (!visit[ny][nx] && find(dessert.begin(), dessert.end(), map[ny][nx]) == dessert.end())		// [중복된 cafe방문 여부와 있는지 판단.]
		{
			dir[i] = true;			// [해당 direction으로 이동했을 경우, 아직 이동하지 않은 direction으로만 이동이 가능하다.]
			DFS(ny, nx, i);
			dir[i] = false;			// Backtracking.
			visit[ny][nx] = false;		// Backtracking. [DFS로 확인하고 되돌아오면서, 다시 원상복귀 시켜주는 작업.]
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