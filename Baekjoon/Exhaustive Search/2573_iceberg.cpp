#include<iostream>
#include<algorithm>
#include<vector>
#include<memory.h>

#define MAX 301

using namespace std;

int N, M;											// N = The size of rows.			M = The size of columns.
vector<pair<int, int>> map[MAX];		// The memory of map. [first = Iceberg's height.		second = count.]
bool visit[MAX][MAX];						// The memory of visited or not.
int dy[4] = { -1, 1, 0, 0 };				// Up, Down.
int dx[4] = { 0,0,-1,1 };					// Left, Right.
pair<int, int> start;							// The start coordinate of iceberg which exists.

bool Separated()			// To figure out whether the iceberg was separated more than two piecces.							
{
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			if (visit[i][j])			// [visit == false] means that the iceberg was connected each other.
				return false;		// [Iceberg�� �������� �ִٸ�, start �������� ��� iceberg�� �湮 �� �� ����.]	
										// [[return == false] �� ��� �湮�� �̷�����ٴ� ���� �ǹ�.]
	return true;				// [[return == true]�� DFS�� ���� ��� iceberg �湮�� �����ߴٴ� ���� �ǹ�.]		
}

void DFS(int y, int x)		// To search all icebergs from start point.
{
	visit[y][x] = false;		// Check the current coordinate as visited successfully.	

	for (int i = 0; i < 4; i++)
	{
		int ny = y + dy[i];	// Up, Down.	
		int nx = x + dx[i];	// Left, Right.

		if (ny < 0 || ny >= N || nx < 0 || nx >= M)			// Overflow area.
			continue;

		if (visit[ny][nx])		// Not visited yet only.
			DFS(ny, nx);		// Search new point.
	}
}

void Check()		// To organize the visited memory based on iceberg.
{						// [Iceberg�� �����ϴ� ��ġ�� visit = true�� check�ϱ� ����.]
	// Initialization.
	memset(visit, false, sizeof(visit));		
	start.first = 0; 
	start.second = 0;	

	bool flag = true;		// To set start point.
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			if (map[i][j].first)		// [Iceberg�� ������ ���, visit = true�� set.]
			{
				visit[i][j] = true;		// Set visited memory.
											
				if (flag)		// It was used only once.
				{
					start.first = i;		// Set start point.
					start.second = j;
					flag = false;
				}
			}
		}
	}
}

void Melting()			// To reorganize iceberg every year.
{							// [Iceberg's height�� �ų� �پ��� ���� �����Ű�� ����.]	
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			if (map[i][j].first)		// The case of iceberg exists.		
			{				// [Iceberg�� �����ϴ� ���.]
				for (int k = 0; k < 4; k++)
				{
					int ny = i + dy[k];	// Search iceberg's surroundings area.
					int nx = j + dx[k];	// [Iceberg�� ��,��,��,�� Ȯ��.]
					
					if (ny < 0 || ny >= N || nx < 0 || nx >= M)		// Overflow area.
						continue;

					if (!map[ny][nx].first)				// [Iceberg�� ���� ����������, count.]
						map[i][j].second++;			// Counts the number of zero area.
				}
			}
		}
	}

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			if (map[i][j].second)
			{
				map[i][j].first -= map[i][j].second;
				map[i][j].second = 0;

				if (map[i][j].first < 0)
					map[i][j].first = 0;
			}
		}
	}
}

bool Iceberg()		// To figure out whether the iceberg still exists.
{
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			if (map[i][j].first)		// The case of iceberg exists.
				return true;				// [Iceberg�� ���� �����ϴ� ���.]
	
	return false;
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin >> N >> M;
	for (int i = 0; i < N; i++)		// The size of rows.
	{
		for (int j = 0; j < M; j++)	// The size of columns.
		{
			int height;
			cin >> height;				// The height of iceberg.
			map[i].push_back(make_pair(height, 0));
		}
	}

	int year = 0;
	while (Iceberg())
	{
		Melting();						// The iceberg's height will be decreased every year.
		year++;

		Check();							// To organize the visited memory based on iceberg.
		DFS(start.first, start.second);		// To search all icebergs from start point.
		if (!Separated())				// To figure out whether the iceberg was separated more than two piecces.			
		{
			cout << year << endl;
			return 0;
		}
	}
	cout << 0 << endl;				// The case of that the iceberg did not separate until it melted completely.
}