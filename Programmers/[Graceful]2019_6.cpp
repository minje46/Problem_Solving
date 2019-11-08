#include<iostream>
#include<algorithm>
#include<string>
#include<vector>
#include<queue>

#define MAX 10001
using namespace std;

vector<string> solution(int total, vector<string> vc)
{
	vector<string> log[MAX];
	for (int i = 0; i < vc.size(); i++)
	{
		string tmp = "";
		for (int j = 0; j < vc[i].length(); j++)
		{
			if (vc[i][j] == ' ')
			{
				log[i].push_back(tmp);
				tmp.clear();
				continue;
			}
			tmp += vc[i][j];
		}
		log[i].push_back(tmp);
	}

	int cnt = 0;
	vector<string> ans;
	queue<pair<int, string>> que;
	//	que.push(make_pair(0, log[0][2]));
	for (int i = 0; i < vc.size(); i++)
	{
		if (cnt > total)
			break;

		if (find(ans.begin(), ans.end(), log[i][0]) != ans.end())		// 이미 성공한 애들.
			continue;

		if (que.empty())		// 이용 가능 상태면, 바로 접속.
		{
			if (log[i][1] == "request")
				que.push(make_pair(i, log[i][2]));
			continue;
		}
		// 이미 이용중인 경우,
		auto cur = que.front();
		if (log[i][1] == "leave")
		{
			if (log[i][0] == log[cur.first][0])		// ID가 같은 경우에만, 시간 비교.
			{
				string m = "";
				m += cur.second[3];	m += cur.second[4];
				int p = stoi(m);
				m.clear();
				m += log[i][2][3];		m += log[i][2][4];
				int c = stoi(m);
				if (c - p >= 1)
				{
					cnt += 1;
					ans.push_back(log[i][0]);
				}
			}
			que.pop();
			continue;
		}

		string mm = "", ss = "";
		mm += cur.second[3];	mm += cur.second[4];
		ss += cur.second[6];		ss += cur.second[7];
		int pm = stoi(mm), ps = stoi(ss);		// que에 있는 시간.

		mm.clear();		ss.clear();
		mm += log[i][2][3];	mm += log[i][2][4];
		ss += log[i][2][6];		ss += log[i][2][7];
		int cm = stoi(mm), cs = stoi(ss);		// 현재 log의 시간.

		if (pm >= cm)		// queue 가 순서상 더 빠른 것.
			continue;
		else
		{
			cs += (cm - pm) * 60;
			if (cs - ps >= 60)
			{
				cnt += 1;
				ans.push_back(log[cur.first][0]);
				que.pop();
			}
		}
	}

	if (cnt < total && !que.empty())
	{
		auto cur = que.front();
		string m = "", s = "";
		m += cur.second[3];	m += cur.second[4];
		s += cur.second[6];	s += cur.second[7];
		int p = stoi(m), se = stoi(s);
		if (p<59)
			ans.push_back(log[cur.first][0]);
		else if (p == 59)
		{
			if (se == 0)
				ans.push_back(log[cur.first][0]);
		}
	}

	return ans;
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);	cout.tie(0);

	//vector<string>vc = {
	//	"woni request 09:12:29",
	//	"brown request 09:23:11",
	//	"brown leave 09:23:44",
	//	"jason request 09:33:51",
	//	"jun request 09:33:56",
	//	"cu request 09:34:02"
	//};
	//vector<string>vc = {
	//	"woni request 09:12:29",
	//	"a request 09:13:29",
	//	"brown request 09:23:11",
	//	"b request 09:23:12",
	//	"c request 09:23:33",
	//	"brown leave 09:23:44",
	//	"jason request 09:33:51",
	//	"jun request 09:33:56",
	//	"cu request 09:34:02",
	//	"d request 09:59:01"
	//};
	vector<string>vc = {
		"woni request 09:12:29",
		"a request 09:13:29",
		"brown request 09:23:11",
		"b request 09:23:12",
		"c request 09:23:33",
		"brown leave 09:23:44",
		"jason request 09:33:51",
		"jun request 09:33:56",
		"cu request 09:34:02",
		"d request 09:59:01"
	};

	vector<string> answer = solution(2000, vc);
	sort(answer.begin(), answer.end());
	for (int i = 0; i < answer.size(); i++)
		cout << answer[i] << endl;
}