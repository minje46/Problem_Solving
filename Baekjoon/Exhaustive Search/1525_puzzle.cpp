#include<iostream>
#include<string>
#include<queue>
#include<map>

#define TARGET 123456789

using namespace std;

const int dy[4] = { -1,1,0,0 };
const int dx[4] = { 0,0,-1,1 };

int input = 0;				// input = The memory of input data.
map<int, int>visit;		// visit = The memory of visited or not.

void BFS()			// To figure out the target number with changed each digit's number based on bfs.
{
	queue<int>que;
	que.push(input);
	visit[input] = 0;
	while (!que.empty())
	{
		auto cur = que.front();
		que.pop();

		string str = to_string(cur);

		if (cur == TARGET)			// Base csae. [Target.]
			return;

		int z = str.find('9');		// The location of empty space.
		int y = z / 3;				// Y coordinate of empty space.
		int x = z % 3;				// X coordinate of empty space.
		for (int i = 0; i < 4; i++)
		{
			int ny = y + dy[i];
			int nx = x + dx[i];

			if (ny < 0 || ny >= 3 || nx < 0 || nx >= 3)	// Overflow.
				continue;

			string tmp = str;
			swap(tmp[y * 3 + x], tmp[ny * 3 + nx]);		// Swap. [Move the empty space to new location.]
			
			int next = stoi(tmp);
			if (!visit.count(next))		// Check there is or not using count. 
			{									// [count:0] means there is none.
				visit[next] = visit[cur] + 1;		// Count the number from current one.
				que.push(next);
			}
		}
	}
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);	cout.tie(0);

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			int num;
			cin >> num;			// Input data.

			if (num == 0)			// Empty space 
				num = 9;			// Change to 9.
			input = input * 10 + num;		// Make as one integer number.
		}
	}

	BFS();			// Do exhaustive search.

	if (!visit.count(TARGET))		// None.
		cout << -1 << endl;
	else				// Output.
		cout << visit[TARGET] << endl;
}