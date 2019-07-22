#include<iostream>
#include<string>

using namespace std;

int **memo;										// Memory of memoization table.									
string s1, s2;										// Input memory.

void Memoization()																// Do memoization of comparison table.
{
	for (int i = 0; i < s2.size(); i++)											// Column.
	{
		for (int j = 0; j < s1.size(); j++)										// Row.
		{
			if (i == 0 || j == 0)													// The first case which has 0 row or 0 column.
			{
				memo[i][j] = 0;													// [0의 column과 row는 0으로 초기화.]
				continue;
			}

			if (s2[i] == s1[j])													//	If both alphabet are same.
				memo[i][j] = memo[i - 1][j - 1] + 1;					// [현재 비교하는 alphabet이 서로 같다면, 이전 memo+1]

			else																		// Both alphabets are not same.
			{
				if (memo[i - 1][j] > memo[i][j - 1])					// [서로 다른 alphabet이라면, 이전 memo의 값을 가져온다.]
					memo[i][j] = memo[i - 1][j];							// Refer the value from left side on memoization.
				else
					memo[i][j] = memo[i][j - 1];							// Refer the value from up side on memoization.
			}
		}
	}
}

int main(void)
{
	cin >> s1;													// Input of first string.
	cin >> s2;													// Input of second string.		
																	// To do memoization.
	s1 = '0' + s1;												// Memoization is started from 0 to build a comparing table.
	s2 = '0' + s2;												// [Memoization은 2개 string을 서로 비교하는 table을 위해 0부터 시작해야한다.]

	memo = new int *[s1.size()];						// Allocate the memory of column array.
	for (int i = 0; i < s1.size(); i++)
		memo[i] = new int[s2.size()];					// Allocate the memroy of row array.

	Memoization();											// Fill the contents of memoization.

	cout << memo[s1.size()-1][s2.size()-1] << endl;		// Output of subsequence's length.
}