#include<iostream>
#include<algorithm>

#define MAX 500001

using namespace std;

int N, M;							// N = The number of cards i have.					M = The number of cards to check.
long long card[MAX];		// card = The memory of cards i have.
long long value;				// value = The temporary memory to get value.
bool check[MAX];			// check = The memory of have or not.

void Binary(int lf, int rt, int idx)		// To figure out the target value is or not.
{	
	int mid = (lf + rt) / 2;		// Middle index.	
	if (card[mid] == value)	// Same or not.
	{
		check[idx] = true;		
		return;
	}

	if (lf >= rt)		// Base case. [Avoid over flow.]
		return;

	if (card[mid] > value)		// Go left.
		Binary(lf, mid, idx);
	else								// Go right.
		Binary(mid + 1, rt, idx);
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> N;
	for (int i = 0; i < N; i++)
		cin >> card[i];			// Input of cards i have.
	sort(card, card + N);		// Ascending sort.

	cin >> M;
	for (int i = 0; i < M; i++)
	{
		cin >> value;				// Input of value to search.
		Binary(0, N - 1, i);		// Binary search.
	}

	for (int i = 0; i < M; i++)
		cout << check[i] << " ";		// Output.
	cout << endl;
}
