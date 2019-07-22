#include<iostream>
#include<algorithm>
#include <vector>
#include<queue>

using namespace std;

int dy[4] = { -1,1,0,0 };	// Up, Down.
int dx[4] = { 0,0,-1,1 };	// Left, Right.
queue<pair<int, int>>que;

bool Square(int y, int x, vector<vector<int>>board)
{
	int N = board[0].size();

	if (y == que.front().first && x == que.front().second)
		return true;

	que.push(make_pair(y, x));

	for (int i = 0; i < 4; i++)
	{
		int ny = y + dy[i];
		int nx = x + dx[i];

		if (ny < 0 || ny >= N || nx < 0 || nx >= N)		// Overflow area.
			continue;

		if (board[ny][nx] != 0)
			Square(ny, nx, board);
	}

	return false;
}

vector<vector<int>> Preprocess(vector<vector<int>> b)
{
	pair<int, int> start;

	for (int i = 0; i < b[0].size(); i++)
	{
		for (int j = 0; j < b[i].size(); j++) 
		{
			if (b[i][j] != 0)
			{
				start.first = i;
				start.second = j;
				goto Exit;
			}
		}
	}
Exit:
	for (int i = start.first; i < b[0].size(); i++)		
	{
		for (int j = start.second; j < b[i].size(); j++) 
		{
			if (i != b[0].size() - 1)
			{
				if (b[i + 1][j] == 0)
				{
					for (int k = i + 1; k < b.size(); k++)
					{
						b[k][j] = -1;
					}
				}
			}
		}
	}
	return b;
}

int solution(vector<vector<int>> board) 
{
	int answer = 0;

	board = Preprocess(board);

	cout << "TEST" << endl;
	return answer;
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	vector<vector<int>> board = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 4, 0, 0, 0}, {0, 0, 0, 0, 0, 4, 4, 0, 0, 0}, {0, 0, 0, 0, 3, 0, 4, 0, 0, 0}, {0, 0, 0, 2, 3, 0, 0, 0, 5, 5}, {1, 2, 2, 2, 3, 3, 0, 0, 0, 5}, {1, 1, 1, 0, 0, 0, 0, 0, 0, 5}};

	cout << solution(board) << endl;
}