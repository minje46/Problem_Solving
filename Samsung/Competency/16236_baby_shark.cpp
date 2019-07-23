#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
#include<string.h>

#define MAX 21
#define BABY_SHARK 9

using namespace std;

struct point		// The memory of shark's movement for queue.
{					// [Queue에서 사용하기 위한 data type 이며, shark의 좌표 및 이동 거리를 저장하는 용도.]	
	int y, x;
	int dist;		// shark's distance.

	const bool operator<(const point &p) const
	{
		if (dist == p.dist)		// Organize the standards when this data structure will be compared each other.
		{							// [해당 structure를 compare할 때의 기준을 재정의.] 
			if (y == p.y)		// When both's distance are same, y coordinate will be compared. And then x coordinate will be compared.
				return x > p.x;	// [두 structure가 서로 같은 distance를 가질 때, y 좌표의 값을 비교하고 x 좌표가 더 큰 것을 true.] 
			return y > p.y;		// [y 좌표의 값이 더 큰 것을 true로 return.]  [priority_queue는 내림차순 default.]
		}
		return dist > p.dist;	// [내림차순으로 sort하기 위해 dist가 더 큰 값을 true로 return.]
	}
};

struct shark	// The memory of shark's movement data.
{					// [shark의 정보를 저장하기 위한 data type 이며, shark의 현재 위치와 weight, 먹은 물고기 수를 저장.]	
	int y, x;
	int cnt = 0;
	int size = 2;

	shark() {}	// Maybe, it is constructor of this data strucutre.		[shark라는 data strucutre를 생성할 때 선언되는 생성자 인듯?]

	shark(int y, int x)	// Another type of constructor.
	{
		this->y = y;
		this->x = x;
	}

	void size_up()	// To resize the shark's weight and count.
	{					// [Shark의 weight과 count를 조정하기 위한 method.]
		cnt = 0;
		size++;
	}
};

bool visit[MAX][MAX];			// The memory of visit.	[해당 좌표의 방문 여부 체크.]		
int arr[MAX][MAX];				// The memory of input's adjacent array. [input을 인접 행렬로 저장.]
int dx[4] = { 0,-1,0,1 };		// up, left, down, right.
int dy[4] = { -1,0,1,0 };		// up, left, down, right.
shark baby;						// The memory of baby shark. [행령 내부에서 움직일 shark.]

int BFS(int N)						// To figure out the total distance shark was moved.
{										// [Baby shark가 움직인 총 거리를 구하기 위한 method.]
	int result = 0;					// The memory of result of total distance.
	priority_queue<point>que;
	que.push({ baby.y, baby.x, 0 });	// The first case.
	visit[baby.y][baby.x] = true;			// [BFS를 시작하기 위한 초기 setting.]
	while (!que.empty())		// Until there is no more coordinate shark could move.
	{									// [Shark가 움직일 수 있는 좌표가 더 이상 없을 때 까지.]
		auto cur = que.top();	// The current shark's coordinate.	[현재 shark의 위치.]
		que.pop();

		if (arr[cur.y][cur.x] != 0 && baby.size > arr[cur.y][cur.x])	// The possible zone shark can eat.
		{								// [Shark가 먹을 수 있는 물고기가 존재하는지 판단.]
			baby.y = cur.y;		// After shark ate, the location of shark will be set again.
			baby.x = cur.x;
			baby.cnt++;			// The number of shark ate.
			arr[cur.y][cur.x] = 0;	// The zone will be initiated as 0 after fish was eaten.

			if (baby.cnt >= baby.size)	// If the number of shark ate is same as it's own weight, it should be bigger.
				baby.size_up();				// [Shark가 먹은 물고기 수가 자신의 몸무게와 같아진다면, 몸무게 증가.]

			memset(visit, false, sizeof(visit));	// The shark's location was reset, so the memory of visit will also be initiated.

			while (!que.empty())			// [Shark가 물고기를 잡아먹고, 위치를 이동했기에 초기화 과정이 필요.]
				que.pop();

			result = cur.dist;		// The distance shark was moved.		[Shark의 움직인 거리.]
		}

		for (int i = 0; i < 4; i++)	// Check the location shark is able to move.
		{									// [Shark가 이동 가능한 상, 좌, 하, 우를 확인.]
			int ny = cur.y + dy[i];	// Up, Left, Down, Right order.
			int nx = cur.x + dx[i];

			if (arr[ny][nx] > baby.size || visit[ny][nx] || ny >= N || ny < 0 || nx < 0 || nx >= N)
				continue;				// [새로운 좌표에 존재하는 물고기가 shark보다 무겁거나, 이미 방문 했을 경우, map을 벗어나는 좌표일 경우 pass.]

			visit[ny][nx] = true;		// The new location will be treated as visited for avoiding duplication.
			que.push({ ny, nx, cur.dist + 1 });		//[좌표의 중복을 방지하기 위해, 방문했다고 간주.]
		}
	}
	return result;					// The total distance shark was moved.		[Shark의 움직인 총 거리.]
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	int N;								// N = The size of map.
	cin >> N;
	for (int i = 0; i < N; i++)	// i = y좌표.
	{									// [다차원 array는 [i] (행)개에 [j] (열)개를 가지는 형식으로 memory를 설정하고, 이는 좌표에서 (y,x) 순서로 접근하는 것과 동일.]	
		for (int j = 0; j < N; j++)// j = x좌표.
		{
			cin >> arr[i][j];
			if (arr[i][j] == BABY_SHARK)	// The location shark is. 
			{											// [Baby shark가 위치하는 좌표.]
				baby = { i,j };
				arr[i][j] = 0;
			}
		}
	}

	cout << BFS(N) << endl;		// The total distance shark was moved.		[Shark의 움직인 총 거리.]
}