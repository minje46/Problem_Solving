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
	int i = s1.size()-1 , j = s2.size()-1;				// It should be started from end. [Backtracking�̱� ������, �Ųٷ� ã�ƾ��Ѵ�.]
	while (memo[i][j] != 0)								// Memo[i][j]=0 means there is no need to search again. [0 ���Ĵ� ã�� �ʿ䰡 ����.]
	{
		if (memo[i][j] == memo[i][j - 1])			// If the value of memo is same as left side's value, it should be moved to left side.
			j--;													// [���� ��ġ�� memo ���� ���� memo�� ���� ���ٸ�, �������� �̵�.]		

		else if (memo[i][j] == memo[i - 1][j])		// If the value of memo is same as up side's value, it should be moved to up side.
			i--;													// [���� ��ġ�� memo ���� ���� memo�� ���� ���ٸ�, �������� �̵�.]

		else if (memo[i][j] - 1 == memo[i - 1][j - 1])	// If the value of memo is different as up side's value and left side's value, it should be moved to diagonal side.
		{
			note.push(i);										// Store the alphabet in subsequence memory.		
			i--;													// [LCS���� backtracking �� ���, memo�� ���ʰ� ������ ���� ��� ���� ��ġ�� -1 ���� ������ �Ǵ��ϰ�,
			j--;													// -1 ���� ���� ���, ���� �밢������ �̵��ϴ� ����� �̿��Ѵ�.]
		}															// [�׷���, ���� memo�� ���� ���� memo�� �� �Ǵ� ���� memo�� ���� ���ٸ�, 
	}																// -1���� ���� ��ġ�� ã�� ���� �̵��Ѵ�.]
}

void Memoization()																// Do memoization of comparison table.
{
	for (int i = 0; i < s1.size(); i++)
	{
		for (int j = 0; j < s2.size(); j++)
		{
			if (i == 0 || j == 0)													// The first case which has 0 row or 0 column.
			{
				memo[i][j] = 0;													// [0�� column�� row�� 0���� �ʱ�ȭ.]
				continue;
			}

			if (s1[i] == s2[j])													//	If both alphabet are same.
				memo[i][j] = memo[i - 1][j - 1] + 1;					// [���� ���ϴ� alphabet�� ���� ���ٸ�, ���� memo+1]

			else																		// Both alphabets are not same.
			{
				if (memo[i - 1][j] > memo[i][j - 1])					// [���� �ٸ� alphabet�̶��, ���� memo�� ���� �����´�.]
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
	s2 = '0' + s2;												// [Memoization�� 2�� string�� ���� ���ϴ� table�� ���� 0���� �����ؾ��Ѵ�.]

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