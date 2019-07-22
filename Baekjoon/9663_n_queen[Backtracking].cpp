#include<iostream>

using namespace std;

int *chess;										// The size of chess board.
int N;												// The number of chess board's size.		
int result = 0;									// The result of N_Queen's method.

bool Promising(int row)					// Judge whether it is correct position or not. [Queen의 위치가 행,열에 알맞은지 판단.]
{						
	for (int column=0; column<row; column++)		// [Parameter로 받은 row에 어느 column에 queen을 배치해야 하는지 loop를 통해 하나씩 확인.]
	{
		if (chess[row] == chess[column] || abs(chess[row] - chess[column]) == (row - column))	// Condition of queen's movement. [Queen의 이동경로 조건.]
			return false;
	}
	return true;
}

void N_queen(int row)						// Find the correct position of queen on chess board.
{
	if (row == N)												// If the row is gonna be same with size of chess board, it means all row have each queen. 
		result++;													// [row(행)을 증가 시키면서 queen을 하나씩 알맞은 자리에 배치하는데, N과 row가 같다는 것은 모든 row에 queen 배치에 성공했다는 것을 의미.]
	
	else															
	{
		for (int column = 0; column < N; column++)	// Judge whether it is correct position or not.
		{																// [Row에 column 위치를 하나씩 대입하면서 queen을 배치할 수 있는지 판단한다.]
			chess[row] = column;								// [(Row,Column)을 1차원 array로 표현한 것.]
			// At first, judging the queen's location is valid or not. Then, do back tracking(adjust location of column) or recursive(Increase row of chess board).
			if (Promising(row))									// [위에서 배치한 queen의 (row,column)위치가 유효한지 판단.]
				N_queen(row + 1);								// [queen의 위치가 유효한다면, 다음 행에 queen을 배치하기 위해 Recursive 진행.]		
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