#include<iostream>

using namespace std;

long long N;	// N = The input data of integer value.			

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);	cout.tie(0);
	//freopen("input.txt", "r", stdin);
	
	int test_case;
	cin >> test_case;
	for (int t = 1; t <= test_case; t++)
	{
		cin >> N;				// Input.

		bool Alice = true;		// Alice = The turn of Alice. And it starts first.
		long long x = 1;		// x = The memory of rule (2x, 2x+1).
		while (N > 0)
		{
			N -= x;
			if (Alice)				// It has binary tree figure.
				x *= 4;

			Alice = !Alice;		// Change the turn.
		}
		if (Alice)					// Winner : Alice.
			cout << "#" << t << " " << "Alice" << "\n";
		else						// Winner : Bob.
			cout << "#" << t << " " << "Bob" << "\n";
	}
}