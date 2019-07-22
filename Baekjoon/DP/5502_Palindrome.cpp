#include<iostream>
#include<string>
#include<algorithm>
#include<stack>

using namespace std;

int N;
string original, opposite;			// original = input memory.			opposite = memory of reversed string.
int memo[5001][5001];			// Memory of memoization table.	
stack<int> note;						// Memory of subsequences.

void LCS()								// Do backtracking to figure out what subsequence is.		
{
	int i = original.size() - 1, j = opposite.size() - 1;		// It should be started from end. [Backtracking�̱� ������, �Ųٷ� ã�ƾ��Ѵ�.]
	while (memo[i][j] != 0)		// Memo[i][j]=0 means there is no need to search again. [0 ���Ĵ� ã�� �ʿ䰡 ����.]
	{
		if (memo[i][j] == memo[i][j - 1])			// If the value of memo is same as left side's value, it should be moved to left side.
			j--;													// [���� ��ġ�� memo ���� ���� memo�� ���� ���ٸ�, �������� �̵�.]	

		else if (memo[i][j] == memo[i - 1][j])		// If the value of memo is same as up side's value, it should be moved to up side.
			i--;													// [���� ��ġ�� memo ���� ���� memo�� ���� ���ٸ�, �������� �̵�.]

		else if (memo[i][j] - 1 == memo[i - 1][j - 1])	// If the value of memo is different as up side's value and left side's value, it should be moved to diagonal side.
		{
			note.push(i);												// Store the alphabet in subsequence memory.		
			i--;															// [LCS���� backtracking �� ���, memo�� ���ʰ� ������ ���� ��� ���� ��ġ�� -1 ���� ������ �Ǵ��ϰ�,
			j--;															// -1 ���� ���� ���, ���� �밢������ �̵��ϴ� ����� �̿��Ѵ�.]
		}																	// [�׷���, ���� memo�� ���� ���� memo�� �� �Ǵ� ���� memo�� ���� ���ٸ�, 
	}																		// -1���� ���� ��ġ�� ã�� ���� �̵��Ѵ�.]
}	

void Memoization()			// Do memoization of comparison table.
{
	for (int i = 0; i <original.size() ; i++)
	{
		for (int j = 0; j < opposite.size(); j++)
		{
			if (i == 0 || j == 0)				// The first case which has 0 row or 0 column.
			{
				memo[i][j] = 0;				// [0�� column�� row�� 0���� �ʱ�ȭ.]
				continue;
			}
			
			if (original[i] == opposite[j])						//	If both alphabet are same.
				memo[i][j] = memo[i-1][j-1] + 1;		// [���� ���ϴ� alphabet�� ���� ���ٸ�, ���� memo+1]
			else														// Both alphabets are not same.
				memo[i][j] = max(memo[i][j - 1], memo[i - 1][j]);	// [���� �ٸ� alphabet�̶��, ���� memo�� ���� �����´�.]
		}
	}
}

int main(void)
{
	cin >> N;					// Input of string's length.
	cin >> original;			// Input of first string.
	
	opposite = original;		// To reverse the string.
	reverse(opposite.begin(), opposite.end());		// Reverse the string in range.

	original = '0' + original;				// Memoization is started from 0 to build a comparing table.
	opposite = '0' + opposite;			// [Memoization�� 2�� string�� ���� ���ϴ� table�� ���� 0���� �����ؾ��Ѵ�.]

	Memoization();			// Fill the contents of memoization.
	LCS();						// Do backtracking to figure out what the longest common Memoization.
	cout << N - note.size() << endl;		// Output of extra string to make palindrome string.
}