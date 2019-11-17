#include<iostream>
#include<memory.h>

using namespace std;

int coin[3];			// coin = The memory of input data.
int target[3];		// target = The memory of target coins.

bool Check()		// To check it is possible or not.
{
	for (int i = 0; i < 3; i++)
	{
		if (coin[i] < target[i])		// Shortage case.	
			return false;
	}
	return true;
}

int Greedy()
{
	int cnt = 0;
	for (int i = 1; i >= 0; i--)
	{
		if (coin[i] < target[i])		// Satisfy the target.					
		{
			int need = target[i] - coin[i];
			if (coin[i + 1] / 11 >= need)		// Bronze to Silver.
			{											// Silver to Gold.		
				coin[i] += need;
				coin[i + 1] -= (need * 11);
				cnt += need;
			}
		}
	}
	
	if (Check())
		return cnt;

	for (int i = 2; i > 0; i--)
	{
		if (coin[i] < target[i])		// Shortage case.					
		{
			int need = target[i] - coin[i];
			int enough = coin[i - 1] - target[i - 1];

			if (enough * 9 >= need)	// Sliver to Bronze.
			{									// Gold to Silver.		
				int n = need / 9;
				if (need % 9 != 0)
					n += 1;
				coin[i] += (n * 9);
				coin[i - 1] -= n;
				cnt += n;
			}
		}
	}
	if (!Check())
		return -1;
	else
		return cnt;
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);	cout.tie(0);

	for (int i = 0; i < 3; i++)
		cin >> coin[i];				// Input data.
	for (int i = 0; i < 3; i++)
		cin >> target[i];				// Target data.

	cout << Greedy() << endl;	// Output.
}
