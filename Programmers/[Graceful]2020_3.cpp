#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>

using namespace std;

int solution(vector<int> prices, vector<int> discounts) 
{
	int answer = 0;	
	priority_queue<int> que;
	for (int i = 0; i < prices.size(); i++)
		que.push(prices[i]);
	
	priority_queue<int> dis;
	for (int i = 0; i < discounts.size(); i++)
		dis.push(discounts[i]);

	while (!que.empty())
	{
		int cur = que.top();
		que.pop();
		if (!dis.empty())
		{
			int d = dis.top();
			dis.pop();

			if (d == 100)
				cur = 0;
			else
				cur = cur / 100 * (100 - d);
		}
		answer += cur;
	}
	return answer;
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);	cout.tie(0);
	
	vector<int> p = { 13000, 88000, 10000 };
	vector<int> d = { 30, 20 };
	cout << solution(p, d) << endl;
}