#include<iostream>

using namespace std;

int board[9][9];									// The size of sudoku board.			
bool stop = false;								// To exit recursive method after completed.

void Print()											// Print all numbers on the board.
{
	for (int row = 0; row < 9; row++)
	{
		for (int col = 0; col < 9; col++)
			cout << board[row][col] << " ";
		cout << endl;
	}
}

bool Promising(int num, int x, int y)		// Judging whether the number is correct or not on (x,y) position.	
{														// [(x,y) 좌표에 num을 1~9까지 차례로 sudoku에 적합한 숫자인지 확인한다.]	
	int rx = x / 3 * 3, ry = y / 3 * 3;			// To get the coordinate (x,y) for square order. [(x,y) 좌표 기준으로 사각형을 확인해야 하기 때문에 좌표 구하는 계산.]
	for (int i = 0; i < 9; i++)					// Increase the position in a row and in a column. [(x,y)좌표 기준으로 행과 열을 +1 씩 증가시키면서 확인.]
		if (board[x][i] == num || board[i][y] == num)	// If there is same number in a row or in a column, do backtracking.
			return false;							// [해당 좌표 행 또는 열에 num이 존재한다는 것은 잘못된 숫자이므로 false로 back tracking.]

	for (int i = rx; i < rx + 3; i++)				// If there is same number in a square, do backtracking.
		for (int j = ry; j < ry + 3; j++)			// [해당 좌표 기준으로 사각형 내에 num이 존재하는지 확인하는 것.]
			if (board[i][j] == num)
				return false;
	return true;										// Do sudoku dfs search. [x,y 좌표에 num이 matching되는 것이 없기 때문에 true 반환. Sudoku DFS 진행하는 것.]
}

void Sudoku()										// Find a empty block(num is zero) first, then compare the number in a order recursively.
{
	if (stop)											// After sudoku is completed, it's gonna be finished.		
		return;

	bool flag = false;								// To exit loop. [loop 중간에 나가기 위함.]
	int x = 0, y = 0;								// Coordinate of empty bolck (num is zero.)

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (board[i][j] == 0)					// It is a empty block. (num is zero.)
			{
				flag = true;
				x = i, y = j;
			}
			if (flag) break;
		}
		if (flag) break;
	}
	
	if (!flag)											// After sudoku is completed, it's gonna be finished.
	{
		stop = true;
		Print();										// Output of the sudoku board.			
	}
		
	for (int i = 1; i < 10; i++)
	{
		if (Promising(i, x, y))					// Judge the number is correct on coordinate (x,y) in a order.
		{												// [좌표 (x,y)에 num이 올바른지 순서대로 promising 여부를 확인한다.]
			board[x][y] = i;						// Update the result which was found on the board. [찾은 num을 board에 업데이트한다.]
			Sudoku();								// Recursively do sudoku again with updated board. [Update한 board로 recursive하게 sudoku를 진행한다.]
			board[x][y] = 0;						// If the updated board was wrong, correct number should be searched again. So it converts block as an empty block.
		}												// [앞서 찾은 num이 추후의 sudoku 진행에 잘못된 값이었다면, 다시 찾아야 하기 때문에 0으로 바꾼뒤,
	}													// Recursive로 진행했던 Sudoku의 다음 num으로 다시 올바른 숫자를 찾도록 진행한다.]

}

int main(void)
{
	for (int row = 0; row < 9; row++)
		for (int col = 0; col < 9; col++)
			cin >> board[row][col];			// Input the whole sudoku board with empty block as a zero.

	Sudoku();
}