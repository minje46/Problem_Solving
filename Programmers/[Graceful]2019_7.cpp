#include<iostream>
#include<string>

using namespace std;

bool Check(string str)		// To check it has duplication or not.
{
	if (str.empty())	
		return true;

	for (int i = 0; i < str.length() - 1; i++)
	{
		if (str[i] == str[i + 1])		// Duplication exists.
			return false;
	}
	return true;
}

string solution(string ans)
{
	while (!Check(ans))		// Until there is no duplication.
	{
		string str = "";
		bool flag = false;
		for (int i = 0; i < ans.length(); i++)
		{
			if (i == 0)		// Base state.
				str += ans[i];
			else if (str[str.size()-1] != ans[i])		// Different character.
			{
				if (flag)		// There is duplication before.
				{
					str.pop_back();		// Delete the previous one.
					flag = false;
				}
				str += ans[i];		// Append the new one.
			}
			else
			{
				if (i == ans.length() - 1)		// The case of all clear.
				{
					if (str[0] == ans[i])		// The first one and last one is same means
						str.clear();				// All elements are duplicated.
				}
				flag = true;
			}
		}
		ans = str;		// Update.
	}
	return ans;
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);	cout.tie(0);

	string str = "browoanoommnaon";
//	string str = "zyelleyz";
//	string str = "abbba";
	cout << solution(str) << endl;
}