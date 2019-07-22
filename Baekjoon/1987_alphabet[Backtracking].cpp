#include<iostream>
#include<vector>

using namespace std;

vector<char> path;						
char **board;										// Size of board.	
int R, C;												// R = rows,	C = columns.
int max_len = 0;									// The length of path.
int dx[] = { 0, 0, -1, 1 };						// Up, Down, Left, Right.
int dy[] = { -1, 1, 0, 0 };						// Up, Down, Left, Right.

bool Promising(char alp)						// Judge whether the alphabet is duplicated or not.
{
	for (int i = 0; i < path.size(); i++)
		if (alp == path[i])						// Compare it is same or not.
			return false;
	
	return true;
}

void Alphabet(int length, int x, int y)		// Find the path based on DFS algorithm.
{
	if (x == 0 && y == 0)						// For the first case.
		path.push_back(board[x][y]);		

	if (max_len < length)						// If this path is the longest one, it should be updated as a max length.
		max_len = length;

	for (int i = 0; i < 4; i++)					// To check direction for X and Y.
	{
		int next_x = x + dx[i];
		int next_y = y + dy[i];
		if ((0 <= next_x && next_x < R) && (0 <= next_y && next_y < C))			// To prevent from overflow.
		{
			if (Promising(board[next_x][next_y]))		// Judge whether the alphabet is duplicated or not.
			{
				path.push_back(board[next_x][next_y]);
				Alphabet(length+1, next_x, next_y);		// Depth First Search.
				path.pop_back();								// To do DFS again with recursive way.
			}
		}
	}
}

int main(void)
{
	cin >> R >> C;												// Input of board size. (Row and Column.)
	board = new char *[R];								
	for (int i = 0; i < R; i++)
	{
		board[i] = new char[C];
		for (int j = 0; j < C; j++)
			cin >> board[i][j];									// Input of board's contents.	
	}

	Alphabet(0, 0, 0);											// len, x, y

	cout << max_len+1 << endl;								// max_len is initialized as a zero.
}