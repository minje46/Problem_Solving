#include<iostream>
#include<algorithm>

#define MAX 11

using namespace std;

int cache[MAX] = { 0, };		// cache = The memory of memoization.

void Organize()		// To figure out the N's memoization.
{
	cache[1] = 1;		// The base condition.
	cache[2] = 2; 
	cache[3] = 4;

	for (int i = 4; i <= 10; i++)
		cache[i] = cache[i - 1] + cache[i - 2] + cache[i - 3];			// The recurrence relation. [Á¡È­½Ä.]
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	Organize();			// Set the whole of memoization from 1 to N;

	int test_case;
	cin >> test_case;
	for (int i = 1; i <= test_case; i++)
	{
		int N;				// N = The target value.
		cin >> N;

		cout << cache[N] << endl;		// The total number of making value N.
	}
}