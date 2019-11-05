#include<iostream>
#include<memory.h>

using namespace std;

int money;			// money = The input data.
int change[9];	// change = The memory of changes. [50000/10000/5000/1000/500/100/50/10/1]

void solution(int mn)
{
	while (mn > 0)
	{
		if (mn >= 50000)
		{
			change[0] += mn / 50000;
			mn %= 50000;
		}
		else if (mn >= 10000)
		{
			change[1] += mn / 10000;
			mn %= 10000;
		}
		else if (mn >= 5000)
		{
			change[2] += mn / 5000;
			mn %= 5000;
		}
		else if (mn >= 1000)
		{
			change[3] += mn / 1000;
			mn %= 1000;
		}
		else if (mn >= 500)
		{
			change[4] += mn / 500;
			mn %= 500;
		}
		else if (mn >= 100)
		{
			change[5] += mn / 100;
			mn %= 100;
		}
		else if (mn >= 50)
		{
			change[6] += mn / 50;
			mn %= 50;
		}
		else if (mn >= 10)
		{
			change[7] += mn / 10;
			mn %= 10;
		}
		else
		{
			change[8] += mn;
			mn = 0;
		}
	}
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);	cout.tie(0);

	memset(change, 0, sizeof(change));
	money = 999999;
	solution(money);
	for (int i = 0; i < 9; i++)
		cout << change[i] << "  ";
	cout << endl;
}
