#include<iostream>
#include<algorithm>

#define MAX 100001

using namespace std;

int N, M;					// N = The number of input data.				M = The total budget.
int input[MAX];		// input = The memory of inpud data.	
int answer = 0;		// answer = The maximum value to support as output.

void Binary(int lf, int rt)		// To do binary search for maximum budget.
{
	if (lf > rt)			// Base case.
		return;

	int mid = (lf + rt) / 2;		
	long long tot = 0;
	for (int i = 0; i < N; i++)
		tot += min(input[i], mid);		// The budget can't be over the maximum support(input).

	if (tot <= M)		// Possible case.
	{
		answer = max(answer, mid);		// Update the maximum budget.
		Binary(mid + 1, rt);		// Go right.
	}
	else if (lf != mid)		// Base case. [To avoid infinity loop.]
		Binary(lf, mid);			// Go left.
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> N;
	for (int i = 0; i < N; i++)
		cin >> input[i];				// Input of support budget.
	cin >> M;
	sort(input, input + N);			// Ascending sort.

	Binary(0, input[N - 1]);		// Binary search.

	cout << answer << endl;		// Output.
}