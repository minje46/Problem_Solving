#include<iostream>
#include<algorithm>
#include<string>
//#pragma warning(disable:4996)

using namespace std;

string num;			// num = The memory of input numbers as string.
int K;					// K = The number of exchanges.
string answer;		// answer = The maximum prize as output.

void DFS(int idx, int cnt)		// To do exhaustive search with combinations.
{
	if (cnt == K)	// Base case. [Exchanging should be treated by K.]
	{
		answer = max(answer, num);		// Compare the maximum value.
		return;
	}

	for (int i = idx; i < num.size(); i++)		// From idx'th number
	{
		for (int j = i + 1; j < num.size(); j++)	// To end of number.
		{
			if (num[i] <= num[j])
			{
				swap(num[i], num[j]);		// Exchange.
				DFS(i, cnt + 1);					// Combinations.
				swap(num[i], num[j]);		// Return.
			}
		}
	}
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

//	freopen("input.txt", "r", stdin);

	int test_case;
	cin >> test_case;
	for (int t = 1; t <= test_case; t++)
	{		
		cin >> num >> K;		// Input.

		answer = "0";		// Initialization.
		DFS(0, 0);			// Exhaustive search.
		cout << "#" << t << " " << answer << endl;		// Output.
	}
}