#include<iostream>
#include<algorithm>
#include<memory.h>
#include<queue>
#include<string>

#define MAX 10001

using namespace std;

int A, B;							// A = The initial integer value.				B = The target integer value.
bool visit[MAX];				// visit = The memory of visited or not.
string answer;					// answer = The minimum combination to shot the target.

pair<int, string> Calculator(int idx, pair<int, string> val)
{
	switch (idx)
	{
	case 0:									// D calculation.
	{
		int tmp = val.first;
		tmp *= 2;					
		if (tmp > 9999)
			tmp %= 10000;
		val = { tmp, val.second + "D" };
		break;
	}
	case 1:									// S calculation.
	{
		int tmp = val.first;
		tmp -= 1;
		if (tmp < 0)
			tmp = 9999;
		val = { tmp, val.second + "S" };
		break;
	}
	case 2:									// L calculation.
	{
		string tmp = to_string(val.first);
		string nval = "";
		for (int i = 1; i < tmp.length(); i++)
			nval += tmp[i];
		nval += tmp[0];
		val = { stoi(nval,nullptr,10), val.second + "L" };
		break;
	}
	case 3:									// R calculation.
	{
		string tmp = to_string(val.first);
		string nval = "";
		nval += tmp[tmp.length() - 1];
		for (int i = 0; i < tmp.length() - 1; i++)
			nval += tmp[i];
		val = { stoi(nval, nullptr, 10), val.second + "R" };
	}
	default:
		break;
	}

	return val;
}

void BFS()
{
	queue<pair<int, string>> que;
	que.push(make_pair(A, ""));
	visit[A] = true;

	while (!que.empty())
	{
		auto cur = que.front();
		que.pop();

		if (cur.first == B)					// Base case.
		{
			answer = cur.second;
			return;
		}

		for (int i = 0; i < 4; i++)
		{
			pair<int, string> nval = Calculator(i, cur);
			
			if (!visit[nval.first])
			{
				que.push(nval);
				visit[nval.first] = true;
			}
		}
	}
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);	cout.tie(0);

	int test_case;
	cin >> test_case;
	for (int t = 1; t <= test_case; t++)
	{	// Initialization.
		memset(visit, false, sizeof(visit));
		answer = "";

		cin >> A >> B;
		
		BFS();

		cout << answer << endl;
	}
}