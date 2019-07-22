#include<iostream>
#include<algorithm>

#define MAX 10001

using namespace std;

int wine[MAX];					// The memory of wine's input data.
long long memo[MAX];		// The memory of memoization to do dynamic programming.

void Recurrence(int N)			// To figure out the maximum wine to drink.
{
	memo[1] = wine[1];						// The base case.
	memo[2] = memo[1] + wine[2];		// The base case.
	
	// [case 1 : 1,2번 째 wine 을 선택한 경우.] [case 2 : 1번 째 wine과, 3번 째 wine을 선택한 경우.] [case 3 : 2,3번 째 wine을 선택한 경우.] 
	for (int i = 3; i <= N; i++)
		memo[i] = max(memo[i - 1], max(memo[i - 2] + wine[i], memo[i - 3] + wine[i - 1] + wine[i]));
}

int main(void)
{
	ios_base::sync_with_stdio(false);

	int N;									// N = The number of whines.
	cin >> N;	
	for (int i = 1; i <= N; i++)
		cin >> wine[i];				// Store the wine's data in itself.
	
	Recurrence(N);					// To figure out the recurrence relation.

	cout << memo[N] << endl;	// Output. [The maximum wine to drink.]
}