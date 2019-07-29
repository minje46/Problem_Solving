#include<iostream>
#include<algorithm>
#include<memory.h>
#include<vector>
#include<cstdlib>
#pragma warning(disable:4996)

#define MAX 21

using namespace std;

int R, C;				// R = The height of map.		C = The width of map.
char map[MAX][MAX];		// map = The memory of original map.
pair<int, int> idx = { 1,1 };		// idx = The location of current index.
int cnt = 0;

void Move(char dir)
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
	{
		idx.first = R;
		cnt++;
	}
	if (idx.first > R)
	{
		idx.first = 1;
		cnt++;
	}
	if (idx.second < 1)
	{
		idx.second = C;
		cnt++;
	}
	if (idx.second > C)
	{
		idx.second = 1;
		cnt++;
	}
}

bool Check()
{
	char dir = ' ';
	int memory = 0;
	pair<int, int> rep = { 0,0 };

	while (map[idx.first][idx.second] != '@')
	{
		if (cnt > MAX*MAX)
			return false;

		int y = idx.first;
		int x = idx.second;

		if (48 <= map[y][x] && map[y][x] <= 57)
		{
			memory = map[y][x] - '0';
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
		
		else if (map[y][x] == '+')
		{
			memory += 1;
			if (memory > 15)
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
			if (memory < 0)
			{
				memory = 15;
				if (rep.first == y && rep.second == x)
					return false;

				rep = { y, x };

			}
			Move(dir);
		}

		else if (map[y][x] == '?')
		{
			int r = rand() % 4;

			if (r == 0)
				dir = '<';
			else if (r == 1)
				dir = '>';
			else if (r == 2)
				dir = '^';
			else if (r == 3)
				dir = 'v';

			Move(dir);
		}
	}

	return true;
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	freopen("input.txt", "r", stdin);

	int test_case;
	cin >> test_case;
	for (int t = 1; t <= test_case; t++)
	{
		memset(map, ' ', sizeof(map));
		idx = { 1,1 };
		cnt = 0;
		cin >> R >> C;
		cin.ignore();					// [입력버퍼('\n') 지우기.]
		for (int i = 1; i <= R; i++)
		{
			for (int j = 1; j <= C; j++)
				cin >> map[i][j];
			cin.ignore();					// [입력버퍼('\n') 지우기.]
		}

		if (Check())
			cout << "#" << t << " " << "YES" << endl;
		else
			cout << "#" << t << " " << "NO" << endl;
	}
}