#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
#include<string.h>

#define MAX 21
#define BABY_SHARK 9

using namespace std;

struct point		// The memory of shark's movement for queue.
{					// [Queue���� ����ϱ� ���� data type �̸�, shark�� ��ǥ �� �̵� �Ÿ��� �����ϴ� �뵵.]	
	int y, x;
	int dist;		// shark's distance.

	const bool operator<(const point &p) const
	{
		if (dist == p.dist)		// Organize the standards when this data structure will be compared each other.
		{							// [�ش� structure�� compare�� ���� ������ ������.] 
			if (y == p.y)		// When both's distance are same, y coordinate will be compared. And then x coordinate will be compared.
				return x > p.x;	// [�� structure�� ���� ���� distance�� ���� ��, y ��ǥ�� ���� ���ϰ� x ��ǥ�� �� ū ���� true.] 
			return y > p.y;		// [y ��ǥ�� ���� �� ū ���� true�� return.]  [priority_queue�� �������� default.]
		}
		return dist > p.dist;	// [������������ sort�ϱ� ���� dist�� �� ū ���� true�� return.]
	}
};

struct shark	// The memory of shark's movement data.
{					// [shark�� ������ �����ϱ� ���� data type �̸�, shark�� ���� ��ġ�� weight, ���� ����� ���� ����.]	
	int y, x;
	int cnt = 0;
	int size = 2;

	shark() {}	// Maybe, it is constructor of this data strucutre.		[shark��� data strucutre�� ������ �� ����Ǵ� ������ �ε�?]

	shark(int y, int x)	// Another type of constructor.
	{
		this->y = y;
		this->x = x;
	}

	void size_up()	// To resize the shark's weight and count.
	{					// [Shark�� weight�� count�� �����ϱ� ���� method.]
		cnt = 0;
		size++;
	}
};

bool visit[MAX][MAX];			// The memory of visit.	[�ش� ��ǥ�� �湮 ���� üũ.]		
int arr[MAX][MAX];				// The memory of input's adjacent array. [input�� ���� ��ķ� ����.]
int dx[4] = { 0,-1,0,1 };		// up, left, down, right.
int dy[4] = { -1,0,1,0 };		// up, left, down, right.
shark baby;						// The memory of baby shark. [��� ���ο��� ������ shark.]

int BFS(int N)						// To figure out the total distance shark was moved.
{										// [Baby shark�� ������ �� �Ÿ��� ���ϱ� ���� method.]
	int result = 0;					// The memory of result of total distance.
	priority_queue<point>que;
	que.push({ baby.y, baby.x, 0 });	// The first case.
	visit[baby.y][baby.x] = true;			// [BFS�� �����ϱ� ���� �ʱ� setting.]
	while (!que.empty())		// Until there is no more coordinate shark could move.
	{									// [Shark�� ������ �� �ִ� ��ǥ�� �� �̻� ���� �� ����.]
		auto cur = que.top();	// The current shark's coordinate.	[���� shark�� ��ġ.]
		que.pop();

		if (arr[cur.y][cur.x] != 0 && baby.size > arr[cur.y][cur.x])	// The possible zone shark can eat.
		{								// [Shark�� ���� �� �ִ� ����Ⱑ �����ϴ��� �Ǵ�.]
			baby.y = cur.y;		// After shark ate, the location of shark will be set again.
			baby.x = cur.x;
			baby.cnt++;			// The number of shark ate.
			arr[cur.y][cur.x] = 0;	// The zone will be initiated as 0 after fish was eaten.

			if (baby.cnt >= baby.size)	// If the number of shark ate is same as it's own weight, it should be bigger.
				baby.size_up();				// [Shark�� ���� ����� ���� �ڽ��� �����Կ� �������ٸ�, ������ ����.]

			memset(visit, false, sizeof(visit));	// The shark's location was reset, so the memory of visit will also be initiated.

			while (!que.empty())			// [Shark�� ����⸦ ��Ƹ԰�, ��ġ�� �̵��߱⿡ �ʱ�ȭ ������ �ʿ�.]
				que.pop();

			result = cur.dist;		// The distance shark was moved.		[Shark�� ������ �Ÿ�.]
		}

		for (int i = 0; i < 4; i++)	// Check the location shark is able to move.
		{									// [Shark�� �̵� ������ ��, ��, ��, �츦 Ȯ��.]
			int ny = cur.y + dy[i];	// Up, Left, Down, Right order.
			int nx = cur.x + dx[i];

			if (arr[ny][nx] > baby.size || visit[ny][nx] || ny >= N || ny < 0 || nx < 0 || nx >= N)
				continue;				// [���ο� ��ǥ�� �����ϴ� ����Ⱑ shark���� ���̰ų�, �̹� �湮 ���� ���, map�� ����� ��ǥ�� ��� pass.]

			visit[ny][nx] = true;		// The new location will be treated as visited for avoiding duplication.
			que.push({ ny, nx, cur.dist + 1 });		//[��ǥ�� �ߺ��� �����ϱ� ����, �湮�ߴٰ� ����.]
		}
	}
	return result;					// The total distance shark was moved.		[Shark�� ������ �� �Ÿ�.]
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	int N;								// N = The size of map.
	cin >> N;
	for (int i = 0; i < N; i++)	// i = y��ǥ.
	{									// [������ array�� [i] (��)���� [j] (��)���� ������ �������� memory�� �����ϰ�, �̴� ��ǥ���� (y,x) ������ �����ϴ� �Ͱ� ����.]	
		for (int j = 0; j < N; j++)// j = x��ǥ.
		{
			cin >> arr[i][j];
			if (arr[i][j] == BABY_SHARK)	// The location shark is. 
			{											// [Baby shark�� ��ġ�ϴ� ��ǥ.]
				baby = { i,j };
				arr[i][j] = 0;
			}
		}
	}

	cout << BFS(N) << endl;		// The total distance shark was moved.		[Shark�� ������ �� �Ÿ�.]
}