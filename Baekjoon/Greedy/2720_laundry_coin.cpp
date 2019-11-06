#include<iostream>
#include<memory.h>

using namespace std;

int change;			// change = The memory of price to exchange.	
int coin[4];			// coin = The memory of coins. [0.25 / 0.10 / 0.05 / 0.01]

void Greedy()
{
	memset(coin, 0, sizeof(coin));
	while (change > 0)
	{
		if (change / 25 > 0)			// Quarter.
		{
			coin[0] += change / 25;
			change %= 25;
		}	
		else if (change / 10 > 0)	// Dime.
		{
			coin[1] += change / 10;
			change %= 10;
		}
		else if (change / 5 > 0)	// Nickel.
		{
			coin[2] += change / 5;
			change %= 5;
		}
		else								// Penny.
		{
			coin[3] += change;
			change = 0;
		}
	}
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);	cout.tie(0);

	int test_case;
	cin >> test_case;
	for (int t = 1; t <= test_case; t++)
	{
		cin >> change;					// Input.
		Greedy();							// Greedy algorithm.
		for (int i = 0; i < 4; i++)
			cout << coin[i] << " ";		// Output.	
		cout << endl;
	}
}