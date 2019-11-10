#include<iostream>
#include <vector>

using namespace std;

vector<int> solution(vector<int> prices)
{
	vector<int> answer;
	for (int i = 0; i<prices.size(); i++)		// In the whole of prices.
	{
		int cnt = 0;											
		for (int j = i + 1; j<prices.size(); j++)		// From current +1 To end.
		{
			cnt++;
			if (prices[i] > prices[j])		// Compare the prices.
				break;
		}
		answer.push_back(cnt);			// Time of maintain. 
	}
	return answer;
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);	cout.tie(0);

	vector<int> prices = { 1, 2, 3, 2, 3 };
	vector<int> ans = solution(prices);
	for (int i = 0; i < ans.size(); i++)
		cout << ans[i] << " ";
}