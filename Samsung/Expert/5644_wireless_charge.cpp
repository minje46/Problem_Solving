#include<iostream>
#include<algorithm>
#include<memory.h>
#include<vector>
//#pragma warning(disable:4996)

#define MAX_U 2
#define MAX_S 11
#define MAX_M 101

using namespace std;

const int dy[5] = { 0,-1,0,1,0 };	// [0:None.	1:Up.		2:Right.]
const int dx[5] = { 0,0,1,0,-1 };	// [3:Down.	4:Left.]

struct Battery		// The total data of battery charge.
{
	int y, x;			// Location.
	int range;		// Coverage.
	int performance;		// Performance.
	bool use;		// Used or not.
};

struct User			// User's location.
{
	int y, x;			// Location.
};

int M, K;				// M = The time to move.				K = The number of battery charger.
vector<Battery>battery;				// battery = The memory of battery charger.
int moved[MAX_U][MAX_M];		// moved = The memory of user's movement.
User user[MAX_U];						// user = The memory of user's location.
int answer = 0;	// answer = The temporary memory to compare max value after dfs.		

void Init()			// To do initialization.
{
	battery.clear();
	memset(moved,  0, sizeof(moved));
	user[0].y = 1, user[0].x = 1;
	user[1].y = 10, user[1].x = 10;
	answer = 0;
}

bool Distance(int a, int b)			// To figure out the distance between user and wireless charger.
{
	int dist = abs(user[a].y - battery[b].y) + abs(user[a].x - battery[b].x);
	
	return dist <= battery[b].range;
}

void DFS(int idx, int tot)		// To do exhaustive search with checking each different wireless charger.
{
	if (idx == MAX_U)	// Base case. [The number of users.]	
	{
		answer = max(answer, tot);		// Compare the maximum total performance.
		return;
	}

	for (int i = 0; i < K; i++)		// In the whole of wireless battery charger.
	{
		if (!battery[i].use && Distance(idx, i))	// Using now or not. + Possible distance.	
		{														// [Battery 사용 여부 + 접근 가능 distance.]
			battery[i].use = true;						// [이미 사용중인 battery만 접근 가능한 경우, 이미 total performance로 계산 되었기 때문에 pass 가능.]	
			DFS(idx + 1, tot + battery[i].performance);	// [2명의 user가 모두 동일한 battery를 이용할 경우, P/2 이기 때문에
			battery[i].use = false;						// 총 합은 하나의 total performance 값이 된다.]
		}
	}
	DFS(idx + 1, tot);
}

int Charger()		// To figure out the maximum total performance.
{
	int result = 0;
	
	DFS(0, 0);		// The start location.
	result += answer;

	for (int i = 0; i < M; i++)		// In the whole of user's movement.
	{
		for (int j = 0; j < MAX_U; j++)	// User A and B's new locatino.
		{
			user[j].y += dy[moved[j][i]];
			user[j].x += dx[moved[j][i]];
		}

		answer = 0;
		DFS(0, 0);
		result += answer;
	}
	return result;		// Accumulated total performance.
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
		Init();

		cin >> M >> K;
		for (int i = 0; i < MAX_U; i++)
		{
			for (int j = 0; j < M; j++)
				cin >> moved[i][j];;
		}
		for (int i = 0; i < K; i++)
		{
			int x, y, c, p;
			cin >> x >> y >> c >> p;
			battery.push_back({ y,x,c,p,false });
		}
		
		cout << "#" << t << " " << Charger() << endl;
	}
}