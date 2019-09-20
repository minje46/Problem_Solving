#include<iostream>
#include<algorithm>

#define MAX 100001

using namespace std;

int N, M;				// N = The number of input array.				M = The number of finding numbers.
int input[MAX];	// input = The memory of input array.	

int Binary(int lf, int rt, int val)			// To figure out whether the value is or not.
{
	if (lf > rt)		// Base case.	
		return 0;

	int mid = (lf + rt) / 2;		// To do binary search.
	if (input[mid] == val)		// Success to find.
		return 1;
	else if (input[mid] > val)	// To left.
		return Binary(lf, mid - 1, val);
	else								// To right.
		return Binary(mid + 1, rt, val);
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> N;
	for (int i = 0; i < N; i++)
		cin >> input[i];				// Input array.
	sort(input, input + N);			// Sort to do binary search.

	cin >> M;
	for (int i = 0; i < M; i++)
	{
		int val;
		cin >> val;						// Finding number.
		cout << Binary(0, N - 1, val) << "\n";
	}
}