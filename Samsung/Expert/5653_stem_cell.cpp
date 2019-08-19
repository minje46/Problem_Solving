#include<iostream>
#include<algorithm>
#include<memory.h>
//#pragma warning(disable:4996)

#define MAX 351

using namespace std;

const int dy[4] = { -1,1,0,0 };		// Up, Down.
const int dx[4] = { 0,0,-1,1 };		// Left, Right.

struct Cell		// The essential data of stem cell.
{
	int state;	// The cell state. [-1:die, 0:empty, 1:active, 2:inactive.]
	int life;		// Life time to live.
	int wait;		// Waiting time to be active or inactive.
	int born;		// The time to be incubated.
	bool move;// Spreaded or not.	
};

int N, M, K;			// N = The hieght of map.			M = The width of map.				K = The time for incubation.
Cell stem[MAX][MAX];		// stem = The memory of the whole of stem cells.

int Alive()		// To count the whole of inactive and active cells.
{
	int cnt = 0;
	for (int i = 0; i < N + K + 2; i++)
	{
		for (int j = 0; j < M + K + 2; j++)
		{
			if (stem[i][j].state > 0)		// [1 : Active.		2 : Inactive.]
				cnt++;
		}
	}
	return cnt;
}

void Spread(int y, int x, int cur)		// To spread the cells around the current one.
{
	for (int k = 0; k < 4; k++)		// Up, Down, Left, Right.
	{
		int ny = y + dy[k];
		int nx = x + dx[k];	

		if (stem[ny][nx].state == 0)		// Empty. [Just incubate.]
		{
			stem[ny][nx].life = stem[y][x].life;	// Host's life time.
			stem[ny][nx].state = 2;		// State.
			stem[ny][nx].wait = 0;		// waiting time.
			stem[ny][nx].born = cur;		// Incubated time.		
			stem[ny][nx].move = false;	// Initialize.
		}

		else	// The case that there is duplicated cells already.
		{	 
			if (stem[ny][nx].state == 2)		// Compare only inactive.	
			{	// [Current time에 incubate된 cell일 수 있기 때문.]
				if (stem[ny][nx].born == cur)	// The stronger one will be survived.
					stem[ny][nx].life = max(stem[ny][nx].life, stem[y][x].life);	// [먼저 퍼진 life 랑 내가 퍼뜨리려는 life랑 비교.]
			}	
		}
	}
}

void Incubation()		// To figure out the stem cell's incubation during time K.
{
	int time = 0;
	while (time < K)	// Until time K.
	{
		for (int i = 0; i < N + K + 2; i++)
		{
			for (int j = 0; j < M + K + 2; j++)
			{
				if (stem[i][j].state == -1)		// Dead.
					continue; 

				else if (stem[i][j].state == 2 && stem[i][j].born < time)		// Inactive.
				{
					stem[i][j].wait += 1;	// [비활로 대기한 시간 증가.]

					if (stem[i][j].wait == stem[i][j].life)	// [대기 완료 시,]
					{
						stem[i][j].state = 1;	// Be active.
					}
				}

				else if (stem[i][j].state == 1)	// Active.
				{
					if (!stem[i][j].move)		// Spread or not.
					{
						Spread(i, j, time);		// Expansion.
						stem[i][j].move = true;
					}

					stem[i][j].wait -= 1;		// [활성에서 보낸 시간 감소.
					if (stem[i][j].wait == 0)	// 시간 다 보냈으면,
						stem[i][j].state = -1;	// Dead.]
				}
			}
		}
		time++;
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
	{	//Initialization.
		memset(stem, 0, sizeof(stem));

		cin >> N >> M >> K;											// [Cell은 [N,M] 범위에서 생성.]
		for (int i = 0 + K / 2 + 1; i < N + K / 2 + 1; i++)		// [K 시간동안 확산될 수 있는 최대 범위는 [(N+K) , (M+K)].]
		{																		// [최대 범위의 가운데에서 cell이 생성되도록 index control.]	
			for (int j = 0 + K / 2 + 1; j < M + K / 2 + 1; j++)	// [중간 범위 = (K/2).]
			{							
				cin >> stem[i][j].life;

				if (stem[i][j].life != 0)		// Stem cell or not.
				{
					stem[i][j].state = 2;		// State.
					stem[i][j].wait = 0;		// waiting time.
					stem[i][j].born = -1;
					stem[i][j].move = false;
				}
			}
		}

		Incubation();

		int answer = Alive();

		cout << "#" << t << " " << answer << endl;
	}
}