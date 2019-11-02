#include<iostream>
#include<algorithm>
#include<memory.h>

#define MAX 21
#define INF 987654321

using namespace std;

const int dy[4] = { -1,1,0,0 };
const int dx[4] = { 0,0,-1,1 };

int N;							// N = The size of map.
int map[MAX][MAX];	// map = The memory of input data.
int area[MAX][MAX];	// area = The memory of each district.
int population[6];		// population = The memory of population in each district.
int answer = INF;			// answer = The minimum gap between max and min population.

void Count()		// To count the number of population in each district.
{
	memset(population, 0, sizeof(population));		// Initialization.
	for (int k = 1; k <= 5; k++)	// From first to five district.
	{
		for (int i = 1; i <= N; i++)
		{
			for (int j = 1; j <= N; j++)
			{
				if (area[i][j] == k)	// Same district.	
					population[k] += map[i][j];		// Population.
			}
		}
	}
}

void Simulation(int y, int x, int d1, int d2)		// To make a each different district.
{
	memset(area, 0, sizeof(area));		// Initialization.
	int idx = 5;	
	area[y][x] = idx;
	for (int d = 1; d <= d1; d++)		// First criteria.
		area[y + d][x - d] = idx;
	for (int d = 1; d <= d2; d++)		// Second criteria.
		area[y + d][x + d] = idx;
	for (int d = 1; d <= d2; d++)		// Third criteria.
		area[y + d1 + d][x - d1 + d] = idx;
	for (int d = 1; d <= d1; d++)		// Fourth criteria.
		area[y + d2 + d][x + d2 - d] = idx;
	for (int i = 1; i <= N; i++)			// Fill the fifth district.
	{
		for (int j = 1; j <= N; j++)
		{
			if (area[i][j] == 5)	// From start position.
			{
				int flag = -1;		
				for (int k = 1; j + k <= N; k++)
				{
					if (area[i][j + k] == 5)		// To next fifth district.	
					{
						flag = j + k;
						break;
					}
				}
				if (flag != -1)		// If there is fifth area,
				{
					for (int k = 1; j + k <= flag; k++)
						area[i][j + k] = idx;		// Fill the district.
				}
			}
		}
	}
		
	idx = 1;
	for (int i = 1; i < y + d1; i++)		// First district.
	{
		for (int j = 1; j <= x; j++)
		{
			if (area[i][j] == 0)		
				area[i][j] = idx;
		}
	}

	idx = 2;
	for (int i = 1; i <= y + d2; i++)	// Second district.
	{
		for (int j = x + 1; j <= N; j++)
		{
			if (area[i][j] == 0)
				area[i][j] = idx;
		}
	}

	idx = 3;
	for (int i = y + d1; i <= N; i++)	// Third district.
	{
		for (int j = 1; j < x - d1 + d2; j++)
		{
			if (area[i][j] == 0)
				area[i][j] = idx;
		}
	}

	idx = 4;
	for (int i = y + d2 + 1; i <= N; i++)		// Fourth district.
	{
		for (int j = x - d1 + d2; j <= N; j++)
			if (area[i][j] == 0)
				area[i][j] = idx;
	}
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);	cout.tie(0);

	cin >> N;
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
			cin >> map[i][j];			// Input data.
	}

	for (int i = 1; i <= N; i++)			// Y range.
	{
		for (int j = 1; j <= N; j++)		// X range.
		{
			for (int a = 1; a <= N; a++)					// D1 range.
			{
				for (int b = 1; i + a + b <= N; b++)		// D2 range.
				{
					if (j - a >= 1 && j - a<j && j + b>j && j + b <= N)
					{
						Simulation(i, j, a, b);			// Make a district.
						Count();								// Count the population.
						int mx = population[1], mn = population[1];		// MAX and Min population.
						bool flag = false;
						for (int k = 1; k <= 5; k++)
						{
							if (population[k] == 0)		// Wrong case.
							{
								flag = true;
								break;
							}
							mx = max(mx, population[k]);
							mn = min(mn, population[k]);
						}
						if (flag)
							continue;
						answer = min(answer, mx - mn);		// Compare the minimum gap.
					}
				}
			}
		}
	}
	cout << answer << endl;			// Output.
}