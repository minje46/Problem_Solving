#include<iostream>
#include<algorithm>
#include<memory.h>
#include<vector>
#include<string>
//#pragma warning(disable:4996)

#define MAX 29

using namespace std;

int N, K;			// N = The number of string.				K = The K'th biggest number.
char str[MAX];				// str = The memory of string.
vector<string> value;		// value = The memory of each splited string as hexa decimal.	

void Hexa_decimal(int n)		// To split up each n'th words as recognize hexa decimal value.
{
	int cnt = 0;
	string tmp;
	for (int i = 0; i < N; i++)	// In full sentence.
	{
		if (cnt == n)		// The standards of split.
		{
			if (find(value.begin(), value.end(), tmp) == value.end())		// Avoid duplication.
				value.push_back(tmp);

			cnt = 0;
			tmp.clear();
		}
		tmp += str[i];		// Append the character as string.
		cnt++;
	}
	if (find(value.begin(), value.end(), tmp) == value.end())		// Avoid duplication.
		value.push_back(tmp);			// For last words after loop.
}

void Rotation()	// To shift right operation in array as rotation.
{
	int n = N / 4;	// The standards of split.
	for (int r = 0; r < n; r++)		// Untill duplicated rotation.
	{
		Hexa_decimal(n);			// Store the hexa decimal value in the current sentence.

		char tmp[MAX];
		copy(str, str + N, tmp);	// Temporary memory.

		for (int i = 1; i < N; i++)
			str[i] = tmp[i - 1];		// Right shift.
		str[0] = tmp[N - 1];		// To deal with over flow.
	}
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	//freopen("input.txt", "r", stdin);

	int test_case;
	cin >> test_case;
	for (int t = 1; t <= test_case; t++)
	{	// Initialization.
		memset(str, ' ', sizeof(str));
		value.clear();
			
		cin >> N >> K;					// Input of the number of sentence and K'th value.	
		for (int i = 0; i < N; i++)
			cin >> str[i];					// Input of original sentence.

		Rotation();		// To rotate the sentence.
		sort(value.begin(), value.end(), greater<string>());		// Descending order.
	
		int answer =stoi(value[K - 1], nullptr, 16);		// Convert hexa decimal to decimal value.
		cout << "#" << t << " " << answer << endl;	// The K'th biggest value as decimal value.
	}
}