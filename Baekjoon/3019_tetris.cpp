#include<iostream>
#include<memory.h>

#define MAX 105

using namespace std;

const int tetris[8][4][4][2] =
{
	{ { { 0,0 },{ 0,0 } ,{ 0,0 } ,{ 0,0 } },{ { 0,0 },{ 0,0 } ,{ 0,0 } ,{ 0,0 } },{ { 0,0 },{ 0,0 } ,{ 0,0 } ,{ 0,0 } },{ { 0,0 },{ 0,0 } ,{ 0,0 } ,{ 0,0 } } },		// Empty space.
{ { { 0,0 },{ -1,0 } ,{ -2,0 } ,{ -3,0 } },	// 'ㅣ' 
{ { 0,0 },{ 0,1 } ,{ 0,2 } ,{ 0,3 } },		// 'ㅡ'
{ { 0,0 },{ 0,0 } ,{ 0,0 } ,{ 0,0 } },
{ { 0,0 },{ 0,0 } ,{ 0,0 } ,{ 0,0 } } },
{ { { 0,0 },{ 0,1 } ,{ -1,0 } ,{ -1,1 } },		// 'ㅁ' 
{ { 0,0 },{ 0,0 } ,{ 0,0 } ,{ 0,0 } },
{ { 0,0 },{ 0,0 } ,{ 0,0 } ,{ 0,0 } },
{ { 0,0 },{ 0,0 } ,{ 0,0 } ,{ 0,0 } } },
{ { { 0,0 },{ 0,1 } ,{ -1,1 } ,{ -1,2 } },			// 'ㄹ 반대' 
{ { 0,0 },{ -1,0 } ,{ -1,-1 } ,{ -2,-1 } },	// 'ㄹ 반대 세운거'	
{ { 0,0 },{ 0,0 } ,{ 0,0 } ,{ 0,0 } },
{ { 0,0 },{ 0,0 } ,{ 0,0 } ,{ 0,0 } } },
{ { { 0,0 },{ 0,1 } ,{ 1,1 } ,{ 1,2 } },			// 'ㄹ' 
{ { 0,0 },{ -1,0 } ,{ -1,1 } ,{ -2,1 } },		// 'ㄹ 세운거'	
{ { 0,0 },{ 0,0 } ,{ 0,0 } ,{ 0,0 } },
{ { 0,0 },{ 0,0 } ,{ 0,0 } ,{ 0,0 } } },
{ { { 0,0 },{ 0,1 } ,{ 0,2 } ,{ -1,1 } },			// 'ㅗ' 
{ { 0,0 },{ -1,0 } ,{ -2,0 } ,{ -1,1 } },		// 'ㅏ'
{ { 0,0 },{ 0,1 } ,{ 0,2 } ,{ 1,1 } },			// 'ㅜ'
{ { 0,0 },{ -1,0 } ,{ -2,0 } ,{ -1,-1 } } },	// 'ㅓ'
{ { { 0,0 },{ 0,1 } ,{ 0,2 } ,{ -1,2 } },			// 'ㄴ 반대' 
{ { 0,0 },{ -1,0 } ,{ -2,0 } ,{ 0,1 } },		// 'L'
{ { 0,0 },{ -1,0 } ,{ -1,1 } ,{ -1,2 } },			// 'ㄱ 반대'
{ { 0,0 },{ 0,1 } ,{ 1,1 } ,{ 2,1 } } },		// 'ㄱ'
{ { { 0,0 },{ -1,0 } ,{ 0,1 } ,{ 0,2 } },			// 'ㄴ' 
{ { 0,0 },{ -1,0 } ,{ -2,0 } ,{ -2,1 } },		// 'L 상하 반대'
{ { 0,0 },{ 0,1 } ,{ 0,2 } ,{ 1,2 } },			// 'ㄱ'
{ { 0,0 },{ 0,1 } ,{ -1,1 } ,{ -2,1 } } },		// 'L 반대'
};

int C, P;							// C = The width of map.				P = The tetris number.
int map[MAX][MAX];		// map = The memory of input data.
int tmp[MAX][MAX];		// tmp = The new memory of map after added tetris block.
int answer = 0;				// answer = The number of possible cases as output.

bool Check(pair<int, int> bk[4])		// To figure out there is empty space between each blocks or not.
{
	for (int i = 0; i < 4; i++)	// New blocks.
	{
		int y = bk[i].first;
		int x = bk[i].second;

		while (y < MAX)			// From new coordinate to basement.
		{
			if (tmp[y++][x] == 0)		// Empty space.
				return false;
		}
	}
	return true;
}

void Simulation(int dir)		// To add tetris block from zero to end of column.
{
	int poly = P;		// The tetris number.
	for (int i = 0; i < C; i++)	// From left To right.	
	{
		memcpy(tmp, map, sizeof(map));		// Copy the original map.
		int dpt;		// Departure point.
		for (int j = 104; j >= 0; j--)
		{
			if (map[j][i] == 0)
			{
				dpt = j;
				break;
			}
		}
		pair<int, int> block[4];			// New coordinates.
		int cnt = 0;
		for (int k = 0; k < 4; k++)
		{
			int ny = dpt + tetris[poly][dir][k][0];
			int nx = i + tetris[poly][dir][k][1];

			if (ny < 0 || ny >= MAX || nx < 0 || nx >= C)		// Overflow.
				break;

			if (tmp[ny][nx] == 0)		// Added blocks.
			{
				tmp[ny][nx] = 1;
				block[cnt] = { ny,nx };
				cnt += 1;
			}
		}

		if (cnt == 4)		// All of blocks were added successfully.
		{
			if (Check(block))		// Check empty space exists or not.
				answer += 1;
		}
	}
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);	cout.tie(0);

	memset(map, 0, sizeof(map));
	cin >> C >> P;					// Input data. [Size of width + Tetris number.]
	for (int i = 0; i < C; i++)
	{
		int h;
		cin >> h;						// Height.
		int j = 104;
		while (h--)
			map[j--][i] = 1;
	}

	for (int i = 0; i < 4; i++)
	{
		if (P == 2 && i >= 1)		// 'ㅁ' figure has only one case.
			break;

		else if (P <= 4 && i >= 2)	// 'ㅣ' and 'ㄹ' figures have only two cases.
			break;
		Simulation(i);		// Check tetris blocks with all of rotated cases.
	}
	cout << answer << endl;		// Output.
}