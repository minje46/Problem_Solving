#include<iostream>

#define MAX 1000001

using namespace std;

long long N, B, C;			// N = The number of classes.		B = The main supervisor's sight.		C = The supportive supervisor's sight.
long long room[MAX];		// room = The memory of class how many students are.
long long cache[MAX];	// cache = The memory of memoization.

int main(void)
{	
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> N;						// The number of classes.	
	for (int i = 0; i < N; i++)
		cin >> room[i];			// How many students they are.
	cin >> B >> C;				// Supervisor's ability.

	for (int i = 1; i <= B; i++)	
		cache[i] = 1;				// Only one main supervisor should stay in each class.

	cache[B + 1] = cache[B] + 1;		// Standards for adding supportive supervisor.
	int cnt = C-1;					// Range of supportive supervisor's ability.
	for (int i = B + 2; i < MAX; i++)
	{
		if (cnt > 0)					// [부감독의 역량(C) 내의 범위는 모두 같은 수의 감독관 수.]
		{
			cache[i] = cache[i - 1];
			cnt -= 1;
		}
		else							// [C의 범위가 초과한다면, 감독 수 +1.]
		{
			cache[i] = cache[i - 1] + 1;
			cnt = C - 1;
		}
	}

	long long answer = 0;
	for (int i = 0; i < N; i++)		// The total number of supervisors.
		answer += cache[room[i]];		// [해당하는 room[]만 cache에서 search.]

	cout << answer << endl;
}