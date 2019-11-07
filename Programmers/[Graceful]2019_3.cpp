#include<iostream>
#include<memory.h>
#include<string>
// 알파벳 치환 문제.
#define MAX 26

using namespace std;

int upper[MAX];		// Upper case.
int lower[MAX];		// Lower case.

string solution(string str)
{
	for (int i = 0; i < MAX; i++)
	{
		upper[i] = 90 - i;
		lower[i] = 122 - i;
	}

	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] >= 65 && str[i] <= 90)		// Upper case.
		{
			int n = str[i] - 65;
			str[i] = upper[n];
		}
		else if (str[i] >= 97 && str[i] <= 122)		// Upper case.
		{
			int n = str[i] - 97;
			str[i] = lower[n];
		}
	}
	return str;
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);	cout.tie(0);

	memset(upper, 0, sizeof(upper));
	memset(lower, 0, sizeof(lower));

	string word = "I love you";
	cout << solution(word) << endl;
}
