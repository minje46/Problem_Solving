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
{														// [(x,y) ��ǥ�� num�� 1~9���� ���ʷ� sudoku�� ������ �������� Ȯ���Ѵ�.]	
	int rx = x / 3 * 3, ry = y / 3 * 3;			// To get the coordinate (x,y) for square order. [(x,y) ��ǥ �������� �簢���� Ȯ���ؾ� �ϱ� ������ ��ǥ ���ϴ� ���.]
	for (int i = 0; i < 9; i++)					// Increase the position in a row and in a column. [(x,y)��ǥ �������� ��� ���� +1 �� ������Ű�鼭 Ȯ��.]
		if (board[x][i] == num || board[i][y] == num)	// If there is same number in a row or in a column, do backtracking.
			return false;							// [�ش� ��ǥ �� �Ǵ� ���� num�� �����Ѵٴ� ���� �߸��� �����̹Ƿ� false�� back tracking.]

	for (int i = rx; i < rx + 3; i++)				// If there is same number in a square, do backtracking.
		for (int j = ry; j < ry + 3; j++)			// [�ش� ��ǥ �������� �簢�� ���� num�� �����ϴ��� Ȯ���ϴ� ��.]
			if (board[i][j] == num)
				return false;
	return true;										// Do sudoku dfs search. [x,y ��ǥ�� num�� matching�Ǵ� ���� ���� ������ true ��ȯ. Sudoku DFS �����ϴ� ��.]
}

void Sudoku()										// Find a empty block(num is zero) first, then compare the number in a order recursively.
{
	if (stop)											// After sudoku is completed, it's gonna be finished.		
		return;

	bool flag = false;								// To exit loop. [loop �߰��� ������ ����.]
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
		{												// [��ǥ (x,y)�� num�� �ùٸ��� ������� promising ���θ� Ȯ���Ѵ�.]
			board[x][y] = i;						// Update the result which was found on the board. [ã�� num�� board�� ������Ʈ�Ѵ�.]
			Sudoku();								// Recursively do sudoku again with updated board. [Update�� board�� recursive�ϰ� sudoku�� �����Ѵ�.]
			board[x][y] = 0;						// If the updated board was wrong, correct number should be searched again. So it converts block as an empty block.
		}												// [�ռ� ã�� num�� ������ sudoku ���࿡ �߸��� ���̾��ٸ�, �ٽ� ã�ƾ� �ϱ� ������ 0���� �ٲ۵�,
	}													// Recursive�� �����ߴ� Sudoku�� ���� num���� �ٽ� �ùٸ� ���ڸ� ã���� �����Ѵ�.]

}

int main(void)
{
	for (int row = 0; row < 9; row++)
		for (int col = 0; col < 9; col++)
			cin >> board[row][col];			// Input the whole sudoku board with empty block as a zero.

	Sudoku();
}