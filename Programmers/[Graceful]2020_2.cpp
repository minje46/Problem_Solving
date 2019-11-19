#include<iostream>
#include<algorithm>
#include<string>
#include<vector>

using namespace std;

int Time(string tmp)
{
	int t = stoi(tmp) + 9;
	if (t >= 24)
		t -= 24;
	return t;
}

vector<int> solution(string logs) 
{
	vector<int> answer;
	for (int i = 0; i < 24; i++)
		answer.push_back(0);

	for (int i = 0; i < logs.length(); i++)
	{
		if (logs[i] == ' ')
		{
			string tmp = "";
			tmp += logs[i + 1];	tmp += logs[i + 2];
			int t = Time(tmp);
			answer[t] += 1;
		}
	}
	return answer;
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);	cout.tie(0);

	string str = "2019/05/01 00:59:192019 / 06 / 01 01:35 : 202019 / 08 / 01 02:01 : 22	2019 / 08 / 01 02:01 : 23	2019 / 08 / 02 03:02 : 352019 / 10 / 03 04 : 05 : 402019 / 10 / 04 06 : 23 : 102019 / 10 / 10 08 : 23 : 202019 / 10 / 12 08 : 42 : 242019 / 10 / 23 08 : 43 : 262019 / 11 / 14 08 : 43 : 29	2019 / 11 / 01 10 : 19 : 022019 / 12 / 01 11 : 23 : 10";
	vector<int> ans = solution(str);
	for (int i = 0; i < ans.size(); i++)
		cout << ans[i] << " ";
}