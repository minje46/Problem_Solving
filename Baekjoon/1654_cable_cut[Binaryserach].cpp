#include<iostream>
#include<algorithm>

#define MAX 10001

using namespace std;

int K, N;							// K = The number of cables possessed.				N = The number of cables to make.
long long cable[MAX];		// cable = The memory of cable's length.
long long answer = 0;		// answer = The maximum length of cable as output.

bool check(long long length)			// To figure out whether it is possible to make N or not.
{
	int cnt = 0;
	for (int i = 0; i < K; i++)
		cnt += (cable[i] / length);		// Total number of cable with length.

	if (cnt >= N	)		// Possible criteria.
		return true;

	return false;		// Impossible.
}

void Simulation()		// To search the longest length.
{
	long long low = 1;
	long long high = cable[K - 1];
	while (low <= high)
	{
		long long mid = (low + high) / 2;
		if (check(mid))
		{
			answer = max(answer, mid);
			low = mid + 1;
		}
		else
			high = mid - 1;
	}
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> K >> N;
	for (int i = 0; i < K; i++)
		cin >> cable[i];			// Input array.

	sort(cable, cable + K);		// Sort to do binary search.	
	Simulation();					// Search the maximum length.
	
	cout << answer << endl;	// Output.
}