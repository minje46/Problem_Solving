#include<iostream>
#include<algorithm>
#include<memory.h>

using namespace std;

int train[4][2];		// train = The memory of input data. [4 : stations][2 : In & Out]
int answer = 0;		// answer = The maximum number of customers as output.

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int total = 0;		// The total number of customers in train.
	for (int i = 0; i < 4; i++)		// Four stations.
	{
		for (int j = 0; j < 2; j++)	// Out & In.
		{
			cin >> train[i][j];

			if (j == 0)		// Out.
				total -= train[i][j];
			else				// In
				total += train[i][j];
		}
		answer = max(answer, total);		// Compare the maximum customers.
	}

	cout << answer << endl;		// Output.
}