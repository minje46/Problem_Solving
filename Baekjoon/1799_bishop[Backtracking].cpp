#include<iostream>
#include<algorithm>

#define MAX 11

using namespace std;

int N;								// N = The size of chess board.
int map[MAX][MAX];		// map = The memory of the chess board.
bool visit_left[20], visit_right[20];				// visit_left = The memory for checking left diagonal.		visit_right = The memory for checking right diagonal.
int answer[2];					// answer = The number of bishop could be set on the chess board with black and white color.

void DFS(int y, int x, int cnt, int color)		// To figure out the number of bishops to set on each color's chess board.
{
	if (x >= N)		// Column overflow.
	{
		y++;			// Next row.
		if (x % 2 == 0)	// [Chess board에서 black, white가 엇갈려서 배치.]
			x = 1;		// [짝수로 끝났다면, 다음 row에서는 홀수 칸에 동일한 color가 배치.]
		else
			x = 0;
	}

	if (y >= N)		// Row overflow.
	{					// [It can be base case.]
		answer[color] = max(answer[color], cnt);	
		return;
	}

	if (map[y][x] && !visit_left[x - y + N - 1] && !visit_right[y + x])	// map[y][x] = Not wall.(Empty space).	
	{					// visit_left[x-y+N-1] = Left diagnoal lines.		visit_right[y+x] = Right diagonal lines.
		visit_left[x - y + N - 1] = visit_right[y + x] = true;		
		DFS(y, x + 2, cnt + 1, color);		// Move to every two steps. Because of black & white separation.
		visit_left[x - y + N - 1] = visit_right[y + x] = false;		// Backtracking.
	}
	DFS(y, x + 2, cnt, color);		// [위의 condition을 만족하지 않은 경우, 다음 칸으로 move.]
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> N;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
			cin >> map[i][j];
	}

	DFS(0, 0, 0, 0);		// [row, column, count, color]
	DFS(0, 1, 0, 1);		// [color : 0(Black), 1(White).]

	cout << answer[0] + answer[1] << endl;		// The number of bishops in black & white area together.
}