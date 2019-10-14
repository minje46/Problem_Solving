#include<iostream>
#include<memory.h>

#define MAX 26

using namespace std;

const int dy[4] = { -1,0,1,0 };
const int dx[4] = { 0,-1,0,1 };
const int pipe[7][4] = { { 1,1,1,1 },{ 0,0,1,1 },{ 1,0,0,1 },{ 1,1,0,0 },{ 0,1,1,0 },{ 1,0,1,0 },{ 0,1,0,1 } };	// All of pipe figure.

int R, C;								// R = The height of map.				C = The width of map.
char map[MAX][MAX];		// map = The memory of input data.
bool visit[MAX][MAX];			// visit = The memory of visited or not.
pair<int, int> start, zone;		// start = The start['M'] location.		zone = The location of missed pipe.

bool Range(int y, int x)			// To check it is overflow or not.
{
	if (y<1 || y>R || x<1 || x>C)		// Overflow.
		return false;
	return true;
}

int Simulation(char fig)			// To figure out the index of pipe.
{
	int idx = 0;
	switch (fig)
	{
	case '+':		
		idx = 0;
		break;
	case '1':
		idx = 1;
		break;
	case '2':
		idx = 2;
		break;
	case '3':
		idx = 3;
		break;
	case '4':
		idx = 4;
		break;
	case '|':
		idx = 5;
		break;
	case '-':
		idx = 6;
		break;
	default:
		break;
	}
	return idx;
}

void DFS(int y, int x)		// To figure out the missed zone based on dfs.
{
	if (zone.first != 0 && zone.second != 0 || map[y][x] == 'Z')		// Base case. [Already zone was founded.]
		return;

	if (map[y][x] == '.')	// Base case. [Missed zone.]
	{
		zone = { y,x };		
		return;
	}

	int dpt = Simulation(map[y][x]);		// The current map's pipe figure.
	for (int i = 0; i < 4; i++)
	{
		int ny = y + dy[i];
		int nx = x + dx[i];

		if (!Range(ny, nx))		// Overflow.
			continue;

		int dst = Simulation(map[ny][nx]);		
		int idx = (i + 2) % 4;		// Opposite way from current direction.
		if (!visit[ny][nx] && pipe[dpt][i] && pipe[dst][idx])		// Not visit yet. + Departure and Destination pipe open.
		{
			visit[ny][nx] = true;
			DFS(ny, nx);
			visit[ny][nx] = false;
		}
	}
}

char Figure()		// To figure out the correct pipe figure in missed zone.
{
	int y = zone.first;
	int x = zone.second;

	bool check[4] = { false, false, false, false };		// To check where is opened.
	for (int i = 0; i < 4; i++)
	{
		int ny = y + dy[i];
		int nx = x + dx[i];

		if (!Range(ny, nx) || map[ny][nx] == '.' || map[ny][nx] == 'M' || map[ny][nx] == 'Z')
			continue;

		int dst = Simulation(map[ny][nx]);
		int dir = (i + 2) % 4;
		if (pipe[dst][dir])
			check[i] = true;
	}

	int idx;
	for (int i = 0; i < 8; i++)
	{
		int cnt = 0;
		for (int j = 0; j < 4; j++)
		{
			if (pipe[i][j] != check[j])
				break;
			cnt++;
		}
		if (cnt == 4)		// Find the correct pipe.
		{
			idx = i;	
			break;
		}
	}

	char fig;
	switch (idx)
	{
	case 0:
		fig = '+';
		break;
	case 1:
		fig = '1';
		break;
	case 2:
		fig = '2';
		break;
	case 3:
		fig = '3';
		break;
	case 4:
		fig = '4';
		break;
	case 5:
		fig = '|';
		break;
	case 6:
		fig = '-';
		break;
	default:
		break;
	}
	return fig;
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0); 	cout.tie(0);

	cin >> R >> C;
	for (int i = 1; i <= R; i++)
	{
		for (int j = 1; j <= C; j++)
		{
			cin >> map[i][j];			// Input data.
			if (map[i][j] == 'M')
				start = { i,j };
		}
	}

	memset(visit, false, sizeof(visit));
	visit[start.first][start.second] = true;

	pair<int, int> st;		// To specify the exact start point with connected pipe location.
	for (int i = 0; i < 4; i++)
	{
		int ny = start.first + dy[i];
		int nx = start.second + dx[i];

		if (!Range(ny, nx))
			continue;

		if (map[ny][nx] != '.' && map[ny][nx] != 'Z')
			st = { ny,nx };
	}
	DFS(st.first, st.second);

	cout << zone.first << " " << zone.second << " " << Figure() << "\n";		// Output.
}