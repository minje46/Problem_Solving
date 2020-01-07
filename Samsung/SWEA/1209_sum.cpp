#include<iostream>
#include<algorithm>
#include<memory.h>
#pragma warning(disable:4996)
#define MAX 100

using namespace std;

int map[MAX][MAX];						// map = The memory of input data.
int answer;										// answer = The biggiest sum value as output.

void Diagonals()				// To figure out each diagonal's sum value.
{
	int lf = 0, rt = 0;
	int j = MAX - 1;
	for (int i = 0; i < MAX; i++)
	{
		lf += map[i][i];
		rt += map[i][j--];
	}
	answer = max(answer, lf);		// Compare the biggest value. 
	answer = max(answer, rt);
}

void Columns()				// To figure out each column's sum value.
{
	for (int j = 0; j < MAX; j++)
	{
		int tot = 0;
		for (int i = 0; i < MAX; i++)
			tot += map[i][j];
		answer = max(answer, tot);		// Compare the biggest value. 
	}
}

void Rows()				// To figure out each row's sum value.
{
	for (int i = 0; i < MAX; i++)
	{
		int tot = 0;
		for (int j = 0; j < MAX; j++)
			tot += map[i][j];
		answer = max(answer, tot);		// Compare the biggest value. 
	}
}

void Simulation()
{
	Rows();
	Columns();
	Diagonals();
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);	cout.tie(0);

	freopen("input.txt", "r", stdin);
	int test_case;
	for (int t = 1; t <= 10; t++)
	{	// Initialization.
		memset(map, 0, sizeof(map));
		answer = 0;

		cin >> test_case;
		for (int i = 0; i < MAX; i++)
		{
			for (int j = 0; j < MAX; j++)
				cin >> map[i][j];
		}

		Simulation();

		cout << "#" << t << " " << answer << endl;
	}
}