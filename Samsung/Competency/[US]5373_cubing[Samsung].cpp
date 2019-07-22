#include<iostream>
#include<algorithm>
#include<vector>
#include<string.h>
#include<memory.h>

using namespace std;

char cube[6][3][3];	// 0 : Up, 1 : Front, 2: Down, 3: Back, 4 : Left, 5 : Right.

void Print()
{
	for (int i = 0; i < 6; i++)
	{
		char c[100];
		switch (i)
		{
		case 0:				// Up.
			strcpy_s(c, "À­¸é / White");
			break;
		case 1:				// Front.
			strcpy_s(c, "¾Õ¸é / Red");
			break;
		case 2:				// Down.
			strcpy_s(c, "¹Ø¸é / Yellow");
			break;
		case 3:				// Back.
			strcpy_s(c, "µÞ¸é / Orange");
			break;
		case 4:				// Left.
			strcpy_s(c, "¿ÞÂÊ¸é / Green");
			break;
		case 5:				// Right.
			strcpy_s(c, "¿À¸¥ÂÊ¸é / Blue");
			break;
		default:
			break;
		}
		cout << endl << c << endl;
		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				cout << cube[i][j][k];
			}
			cout << endl;
		}
	}
}

void Rotate_LR(int side, bool cycle)
{
	if (cycle)			// Clock wise.
	{
		for (int k = 0; k < 3; k++)		// À§->¾Õ
			swap(cube[0][k][side], cube[1][k][side]);

		for (int k = 0, j = 2; k < 3; k++, j--)	// ¾Õ->¹Ø
			swap(cube[0][k][side], cube[2][j][side]);

		for (int k = 0, j = 2; k < 3; k++, j--)	// ¹Ø->µÚ
			swap(cube[0][j][side], cube[3][k][side]);
	}
	else		// Counter clock wise.
	{
		for (int k = 0, j = 2; k < 3; k++, j--)		// À§->µÚ.
			swap(cube[0][k][side], cube[3][j][side]);

		for (int k = 0, j = 2; k < 3; k++, j--)	// µÚ->¹Ø.
			swap(cube[0][j][side], cube[2][k][side]);

		for (int k = 0; k < 3; k++)	// ¹Ø->¾Õ.
			swap(cube[0][k][side], cube[1][k][side]);
	}
}

void Rotate_FB(int a, int b, bool cycle)
{
	if (cycle)		// Clock wise.
	{
		for (int k = 0; k < 3; k++)		// À§->¿À
			swap(cube[0][a][k], cube[5][k][b]);

		for (int k = 0, j = 2; k < 3; k++, j--)	// ¿À->¹Ø 
			swap(cube[0][a][j], cube[2][a][k]);

		for (int k = 0, j = 2; k < 3; k++, j--)	// ¹Ø->¿Þ
			swap(cube[0][a][j], cube[4][k][a]);
	}
	else				// Counter clock wise.
	{
		for (int k = 0, j = 2; k < 3; k++, j--)		// À§->¿Þ
			swap(cube[0][a][j], cube[4][k][a]);

		for (int k = 0, j = 2; k < 3; k++, j--)		// ¿Þ->¹Ø
			swap(cube[0][a][j], cube[2][a][k]);

		for (int k = 0; k < 3; k++)		// ¹Ø->¿À
			swap(cube[0][a][k], cube[5][k][b]);
	}
}

void Rotate_UD(int side, int row, bool cycle)
{
	if (cycle)
	{
		for (int k = 0; k < 3; k++)		// ¾Õ->ÁÂ.
			swap(cube[1][row][k], cube[4][row][k]);

		for (int k = 0, j = 2; k < 3; k++, j--)		// ÁÂ->µÚ.
			swap(cube[1][row][k], cube[3][row][j]);

		for (int k = 0; k < 3; k++)		// µÚ->¿ì.
			swap(cube[1][row][k], cube[5][row][k]);

		char temp[3] = {};
		for (int k = 0; k < 3; k++)		// À§->À§
			swap(cube[side][0][k], temp[k]);

		for (int k = 0; k < 3; k++)		// À§->À§
			swap(temp[k], cube[side][k][2]);
//			swap(cube[side][0][k], cube[side][k][2]);
		for (int k = 0, j = 2; k < 3; k++, j--)		// À§->À§
			swap(cube[side][2][j], temp[k]);
			//swap(cube[side][0][k], cube[side][2][j]);
		for (int k = 0, j = 2; k < 3; k++, j--)		// À§->À§
			swap(cube[side][k][0], temp[j]);
			//swap(cube[side][0][k], cube[side][j][0]);
		for (int k = 0, j = 2; k < 3; k++, j--)		// À§->À§
			swap(cube[side][0][k], temp[j]);
	}
	else
	{
		for (int k = 0; k < 3; k++)		// ¾Õ->¿À.
			swap(cube[1][row][k], cube[5][row][k]);

		for (int k = 0, j = 2; k < 3; k++, j--)		// ¿À->µÚ
			swap(cube[1][row][k], cube[3][row][j]);

		for (int k = 0; k < 3; k++)		// µÚ->ÁÂ
			swap(cube[1][row][k], cube[4][row][k]);


		for (int k = 0, j = 2; k < 3; k++, j--)		// À§->À§
			swap(cube[side][0][k], cube[side][j][0]);
		for (int k = 0, j = 2; k < 3; k++, j--)		// À§->À§
			swap(cube[side][0][k], cube[side][2][j]);
		for (int k = 0; k < 3; k++)		// À§->À§
			swap(cube[side][0][k], cube[side][k][2]);
	}
}

void Original()
{
	for (int i = 0; i < 6; i++)	// Initialize the cube.
	{
		char color;
		switch (i)
		{
		case 0:				// Up.
			color = 'w';		// White.
			break;
		case 1:				// Front.
			color = 'r';		// Red.
			break;
		case 2:				// Down.
			color = 'y';		// Yellow.
			break;
		case 3:				// Back.
			color = 'o';		// Orange.
			break;
		case 4:				// Left.
			color = 'g';		// Green.
			break;
		case 5:				// Right.
			color = 'b';		// Blue.
			break;

		default:
			break;
		}
		for (int j = 0; j < 3; j++)
			for (int k = 0; k < 3; k++)
				cube[i][j][k] = color;
	}
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	int T;				// T = The number of test case.
	cin >> T;
	while (T--)
	{
		Original();
		int N;			// N = The number of rotations.
		cin >> N;
		for (int i = 0; i < N; i++)
		{
			char dir[10];
			cin >> dir;

			bool clock;
			if (dir[1] == '+')			// Clock wise.
				clock = true;
			else							// Counter clock wise.
				clock = false;

			switch (dir[0])
			{
			case 'U':			// Up -> i[0].	
				Rotate_UD(0, 0, clock);
				break;
			case 'D':			// Down -> i[2].
				Rotate_UD(2, 2, !clock);
				break;

			case 'F':			// Front -> i[1].	
				Rotate_FB(2, 0, clock);
				break;
			case 'B':			// Back -> i[3].
				Rotate_FB(0, 2, !clock);
				break;

			case 'L':			// Left -> i[4].
				Rotate_LR(0, clock);
				break;
			case 'R':			// Right -> i[5].	
				Rotate_LR(2, !clock);
				break;

			default:
				break;
			}
			Print();
		}
		/*
		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < 3; k++)
				cout << cube[0][j][k];
			cout << endl;
		}
		*/
	}
}