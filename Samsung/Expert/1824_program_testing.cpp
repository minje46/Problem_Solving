#include<iostream>
#include<memory.h>
#include<cstdlib>
//#pragma warning(disable:4996)

#define MAX 21

using namespace std;

int R, C;				// R = The height of map.		C = The width of map.
char map[MAX][MAX];		// map = The memory of original map.
int visit[MAX][MAX];			// visit = The memory of visited value to figure out loop or not.
int cnt[MAX][MAX];			// cnt = The memory of counting same visited.
pair<int, int> idx = { 1,1 };	// idx = The location of current index.

void Move(char dir)			// To move specific direction.
{
	if (dir == ' ' || dir == '>')
		idx.second += 1;
	else if (dir == '<')
		idx.second -= 1;
	else if (dir == 'v')
		idx.first += 1;
	else if (dir == '^')
		idx.first -= 1;
	
	// Overflow.
	if (idx.first < 1)
		idx.first = R;
	if (idx.first > R)
		idx.first = 1;
	if (idx.second < 1)
		idx.second = C;
	if (idx.second > C)
		idx.second = 1;
}

bool Check()			// To interpret the character.		
{
	idx = { 1,1 };		// Initialization.
	char dir = ' ';
	int memory = 0;
	pair<int, int> rep = { 0,0 };

	while (map[idx.first][idx.second] != '@')		// End condition.
	{
		int y = idx.first;
		int x = idx.second;

		if (cnt[y][x] > MAX)		// Base case.	[To avoid loop.]
			return false;

		if (visit[y][x] != -1 && visit[y][x] == memory)		// Count the same visited. 
			cnt[y][x] += 1;												// It might be factor of loop.
		visit[y][x] = memory;		// To remember the current memory when visited this location.	
			
		if (map[y][x] == '+')
		{
			memory += 1;
			if (memory > 15)			// For + loop, using location.
			{
				memory = 0;
				if (rep.first == y && rep.second == x)
					return false;
				rep = { y, x };
			}
			Move(dir);
		}

		else if (map[y][x] == '-')
		{
			memory -= 1;
			if (memory < 0)			// For - loop, using location.
			{
				memory = 15;
				if (rep.first == y && rep.second == x)
					return false;
				rep = { y, x };
			}
			Move(dir);
		}
		
		else if (48 <= map[y][x] && map[y][x] <= 57)
		{
			memory = map[y][x] - '0';		// Character to Integer.
			visit[y][x] = memory;
			Move(dir);
		}

		else if (map[y][x] == '>' || map[y][x] == '<' || map[y][x] == '^' || map[y][x] == 'v')
		{
			dir = map[y][x];
			Move(dir);
		}

		else if (map[y][x] == '_')
		{
			if (memory == 0)
				dir = '>';
			else
				dir = '<';
			Move(dir);
		}

		else if (map[y][x] == '|')
		{
			if (memory == 0)
				dir = 'v';
			else
				dir = '^';
			Move(dir);
		}

		else if (map[y][x] == '.')
			Move(dir);

		else if (map[y][x] == '?')			// To check all direction it can move.
		{
			map[y][x] = '>';
			memset(visit, -1, sizeof(visit));
			memset(cnt, 0, sizeof(cnt));
			if (Check())
				return true;

			map[y][x] = '<';
			memset(visit, -1, sizeof(visit));
			memset(cnt, 0, sizeof(cnt));
			if (Check())
				return true;

			map[y][x] = '^';
			memset(visit, -1, sizeof(visit));
			memset(cnt, 0, sizeof(cnt));
			if (Check())
				return true;

			map[y][x] = 'v';
			memset(visit, -1, sizeof(visit));
			memset(cnt, 0, sizeof(cnt));
			if (Check())
				return true;
			// If all cases are fail to finish, it would be wrong map.
			return false;
		}
	}
	return true;
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	//freopen("input.txt", "r", stdin);

	int test_case;
	cin >> test_case;
	for (int t = 1; t <= test_case; t++)
	{
		memset(map, ' ', sizeof(map));
		memset(visit, -1, sizeof(visit));
		memset(cnt, 0, sizeof(cnt));
		cin >> R >> C;
		cin.ignore();					// [입력버퍼('\n') 지우기.]
		bool flag = false;
		for (int i = 1; i <= R; i++)
		{
			for (int j = 1; j <= C; j++)
			{
				cin >> map[i][j];
				if (map[i][j] == '@')
					flag = true;
			}
			cin.ignore();					// [입력버퍼('\n') 지우기.]
		}

		if (flag && Check())
			cout << "#" << t << " " << "YES" << endl;
		else
			cout << "#" << t << " " << "NO" << endl;
	}
}