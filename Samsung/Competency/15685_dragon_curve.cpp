#include<iostream>
#include<vector>

#define MAX 101

using namespace std;

int N;									// N = The number of dragon curves.
bool visit[MAX][MAX];			// visit = The memory of visited or not.
int dy[4] = { 0, -1, 0, 1 };	// [0 : Right.		1 : Up.]
int dx[4] = { 1, 0, -1, 0 };	// [2 : Left,		3 : Down.]
vector<int> dir;					// dir = The memory of start direction what dragon curve has.

int Square()		// To check how many squares they are.
{
	int cnt = 0;		// Count value.
	for (int i = 0; i < MAX - 1; i++)
	{
		for (int j = 0; j < MAX - 1; j++)
		{
			if (visit[i][j] && visit[i][j + 1] && visit[i + 1][j + 1] && visit[i + 1][j])		// Square condition.
				cnt++;
		}
	}
	return cnt;
}

void Curve(int y, int x, int generation)			// To figure out the dragon curve with location(y,x) and generation.
{
	for (int i = 1; i <= generation; i++)			// From one generation to end generation.
	{
		int len = dir.size() - 1;						
		for (int j = len; j >= 0; j--)				// For reverse order.
			dir.push_back((dir[j] + 1) % 4);	// [Dragon curve K�� K-1���� �����ϰ� �ִ� stack���� �������� dir+1�� ���� ������.]
	}

	visit[y][x] = true;		// Check dragon curve on coordinate.
	for (int k = 0; k < dir.size(); k++) 
	{
		y += dy[dir[k]];		// [direction�� 0~4���� ������ �°� ����Ǿ� �ֱ⿡,
		x += dx[dir[k]];		// value�� �´� direction���� �����ϸ� �ȴ�.]
		visit[y][x] = true;	// Visit check.
	}
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> N;
	for (int i = 0; i < N; i++)
	{
		int x, y, d, g;			// Location(x,y), direction, generation.
		cin >> x >> y >> d >> g;

		dir.clear();				// For every new input.
		dir.push_back(d);	// Base direction.
		Curve(y, x, g);		// To do dragon curve.
	}
	
	cout << Square() << endl;		// The number of squares on coordinate.
}