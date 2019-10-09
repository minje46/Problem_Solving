#include<iostream>
#include<memory.h>

#define MAX 101

using namespace std;

int N;								// N = The number of problems.
int score[MAX];				// socre = The memory of input data.
bool cache[MAX*MAX];	// cache = The memory of memoization.

void Simulation(int tot)		// To check all of scores by brute force.
{
	cache[0] = true;			// Base case.
	for (int i = 0; i < N; i++)			// In whole of scores.
	{
		for (int j = tot; j >= 0; j--)		// From zero to the maximum total value.
		{
			if (cache[j])		// Possible score.
				cache[j + score[i]] = true;	// Score case + The current score.
		}
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
		memset(score, 0, sizeof(score));
		memset(cache, false, sizeof(cache));

		int tot = 0;
		cin >> N;				
		for (int i = 0; i < N; i++)
		{
			cin >> score[i];			// Input.
			tot += score[i];
		}

		Simulation(tot);				// Dynamic Programming.

		int answer = 0;				// answer = The number of all of cases as output.
		for (int i = 0; i < MAX*MAX; i++)
		{
			if (cache[i])				// Possible score.
				answer += 1;
		}
		cout << "#" << t << " " << answer << endl;		// Output.
	}
}