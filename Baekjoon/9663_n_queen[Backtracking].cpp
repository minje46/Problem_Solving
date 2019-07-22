#include<iostream>

using namespace std;

int *chess;										// The size of chess board.
int N;												// The number of chess board's size.		
int result = 0;									// The result of N_Queen's method.

bool Promising(int row)					// Judge whether it is correct position or not. [Queen�� ��ġ�� ��,���� �˸����� �Ǵ�.]
{						
	for (int column=0; column<row; column++)		// [Parameter�� ���� row�� ��� column�� queen�� ��ġ�ؾ� �ϴ��� loop�� ���� �ϳ��� Ȯ��.]
	{
		if (chess[row] == chess[column] || abs(chess[row] - chess[column]) == (row - column))	// Condition of queen's movement. [Queen�� �̵���� ����.]
			return false;
	}
	return true;
}

void N_queen(int row)						// Find the correct position of queen on chess board.
{
	if (row == N)												// If the row is gonna be same with size of chess board, it means all row have each queen. 
		result++;													// [row(��)�� ���� ��Ű�鼭 queen�� �ϳ��� �˸��� �ڸ��� ��ġ�ϴµ�, N�� row�� ���ٴ� ���� ��� row�� queen ��ġ�� �����ߴٴ� ���� �ǹ�.]
	
	else															
	{
		for (int column = 0; column < N; column++)	// Judge whether it is correct position or not.
		{																// [Row�� column ��ġ�� �ϳ��� �����ϸ鼭 queen�� ��ġ�� �� �ִ��� �Ǵ��Ѵ�.]
			chess[row] = column;								// [(Row,Column)�� 1���� array�� ǥ���� ��.]
			// At first, judging the queen's location is valid or not. Then, do back tracking(adjust location of column) or recursive(Increase row of chess board).
			if (Promising(row))									// [������ ��ġ�� queen�� (row,column)��ġ�� ��ȿ���� �Ǵ�.]
				N_queen(row + 1);								// [queen�� ��ġ�� ��ȿ�Ѵٸ�, ���� �࿡ queen�� ��ġ�ϱ� ���� Recursive ����.]		
		}
	}
}

int main(void)
{
	cin >> N;														// Input the size of chess board.	
	chess = new int[N];											// Make it as an one dimension array.

	N_queen(0);													// Start in first row of chess board.	
	cout << result << endl;										// Output the result of total method with queen's correct position.
}