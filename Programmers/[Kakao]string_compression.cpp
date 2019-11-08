#include<iostream>
#include <string>
#include<vector>

using namespace std;

int solution(string s)			// To compress the duplicated words in a sequence.
{
	string answer = s;
	int n = s.length() / 2;
	for (int k = 1; k <= n; k++)	// Compression length. [From 1 To n]
	{
		string res = "";
		for (int i = 0; i < s.length(); i += k)		// In a string.
		{
			if (i + k >= s.length())	//	 Overflow.
			{
				for (int j = i; j < s.length(); j++)
					res += s[j];
				break;
			}
			string tmp = "";
			for (int j = i; j < i + k; j++)		// Comparison words.
				tmp += s[j];
			int cnt = 1;
			bool cont = true;					// To check how many duplication exists.
			for (int j = i + k; j < s.length(); j += k)		// Check the duplication.
			{
				bool flag = false;				// To check the duplication exists or not. 
				for (int r = 0; r < k; r++)
				{
					if (tmp[r] != s[j + r])	// Duplication in a sequence.
					{
						cont = false;
						break;
					}
					flag = true;
				}
				if (!cont)
					break;
				if (flag)
					cnt += 1;
			}
			if (cnt > 1)		// Duplication exists.
			{
				res += to_string(cnt);
				i += (cnt - 1)*k;
			}
			res += tmp;
		}
		if (answer.length() > res.length())		// Compare the shortest words.
			answer = res;
	}
	return answer.length();
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);	cout.tie(0);

//	string str = "aabbaccc";
//	string str = "ababcdcdababcdcd";
//	string str = "abcabcabcabcdededededede";
	string str = "xababcdcdababcdcd";
	cout << solution(str) << endl;
}