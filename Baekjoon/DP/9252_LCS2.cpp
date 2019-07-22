#include<iostream>
#include<cstdio>
#include<string>
#include<stack>

using namespace std;

int **memo;										// Memory of memoization table.									
string s1, s2;										// Input memory.
stack<int> note;									// Memory of subsequences.

void LCS()														// Do backtracking to figure out what subsequence is.			
{	
	int i = s1.size()-1 , j = s2.size()-1;				// It should be started from end. [Backtracking이기 때문에, 거꾸로 찾아야한다.]
	while (memo[i][j] != 0)								// Memo[i][j]=0 means there is no need to search again. [0 이후는 찾을 필요가 없다.]
	{
		if (memo[i][j] == memo[i][j - 1])			// If the value of memo is same as left side's value, it should be moved to left side.
			j--;													// [현재 위치의 memo 값이 왼쪽 memo의 값이 같다면, 왼쪽으로 이동.]		

		else if (memo[i][j] == memo[i - 1][j])		// If the value of memo is same as up side's value, it should be moved to up side.
			i--;													// [현재 위치의 memo 값이 위쪽 memo의 값이 같다면, 왼쪽으로 이동.]

		else if (memo[i][j] - 1 == memo[i - 1][j - 1])	// If the value of memo is different as up side's value and left side's value, it should be moved to diagonal side.
		{
			note.push(i);										// Store the alphabet in subsequence memory.		
			i--;													// [LCS에서 backtracking 할 경우, memo의 왼쪽과 위쪽의 값이 모두 현재 위치의 -1 값과 같은지 판단하고,
			j--;													// -1 값과 같을 경우, 왼쪽 대각선으로 이동하는 방식을 이용한다.]
		}															// [그래서, 현재 memo의 값이 왼쪽 memo의 값 또는 위쪽 memo의 값과 같다면, 
	}																// -1값과 같은 위치를 찾기 위해 이동한다.]
}

void Memoization()																// Do memoization of comparison table.
{
	for (int i = 0; i < s1.size(); i++)
	{
		for (int j = 0; j < s2.size(); j++)
		{
			if (i == 0 || j == 0)													// The first case which has 0 row or 0 column.
			{
				memo[i][j] = 0;													// [0의 column과 row는 0으로 초기화.]
				continue;
			}

			if (s1[i] == s2[j])													//	If both alphabet are same.
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

	LCS();														// Do backtracking to figure out what the longest common Memoization.
	cout << note.size()	<< endl;							// Output of Memoization's length.
	while (!note.empty())
	{
		cout << s1[note.top()];							// Output of LCS's contents.
		note.pop();
	}
}