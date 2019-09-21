#include<iostream>
#include<algorithm>

#define MAX 1000001

using namespace std;

long long N, M;				// N = The number of trees.				M = The length of tree to get.
long long height[MAX];	// height = The memory of tree's height.
long long answer = 0;		// answer = The longest length to cut.

bool Check(int len)			// To figure out whether it is possible to make M or not.
{
	long long cnt = 0;
	for (int i = 0; i < N; i++)
	{
		if (height[i] - len > 0)		// Longer than standard length.
			cnt += (height[i] - len);
	}

	if (cnt >= M)		// Possible criteria.
		return true;
	else
		return false;
}

void Simulation()				// To search the longest length.
{
	long long lf = 1;			// From 1
	long long rt = height[N - 1];			// To longest length.
	while (lf <= rt)			// Base case. [left couldn't go over the middle or right one.]
	{
		long long mid = (lf + rt) / 2;
		if (Check(mid))	// Check wheter it is possible to make M'th trees.
		{
			answer = max(answer, mid);
			lf = mid + 1;
		}
		else
			rt = mid - 1;
	}
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> N >> M;
	for (int i = 0; i < N; i++)
		cin >> height[i];				// Input array.

	sort(height, height + N);		// Sort to do binary search.	
	Simulation();						// Search the maximum length.

	cout << answer << endl;		// Output.
}