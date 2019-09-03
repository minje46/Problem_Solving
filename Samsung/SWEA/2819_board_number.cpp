#include<iostream>
#include<memory.h>
#include<set>
#include<string>
//#pragma warning(disable:4996)

#define MAX 4

using namespace std;

const int dy[4] = { -1,1,0,0 };
const int dx[4] = { 0,0,-1,1 };

int map[MAX][MAX];		// map = The memory of original input data.
set<string> st;				// st = The memory of valid strings.
int answer = 0;				// answer = The number of valid value as output.

void DFS(int y, int x, string str)		// To figure out the number's combination on the board.
{
	if (str.size() == 7)		// Base case.	[The fixed size of number.]
	{
		st.insert(str);			// If there is duplicate one, it doesn't be inserted.
		return;					// That's because <set> data structure was used.
	}

	for (int i = 0; i < 4; i++)	// Four directions.
	{
		int ny = y + dy[i];
		int nx = x + dx[i];

		if (ny < 0 || ny >= MAX || nx < 0 || nx >= MAX)		// Overflow.
			continue;

		string tmp = to_string(map[ny][nx]);		// Append.
		DFS(ny, nx, str.append(tmp));				// Next one.
		str.pop_back();									// Return to previous.
	}
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);

//	freopen("input.txt", "r", stdin);

	int test_case;
	cin >> test_case;
	for (int t = 1; t <= test_case; t++)
	{	// Initialization.
		memset(map, 0, sizeof(map));
		st.clear();

		for (int i = 0; i < MAX; i++)
		{
			for (int j = 0; j < MAX; j++)
				cin >> map[i][j];			// Input.
		}

		for (int i = 0; i < MAX; i++)
		{
			for (int j = 0; j < MAX; j++)
				DFS(i, j, to_string(map[i][j]));		// Exhaustive search.
		}

		answer = st.size();
		cout << "#" << t << " " << answer << endl;		// Output.
	}
}