// Failure rate.
#include<iostream>
#include<algorithm>
#include <string>
#include <vector>
#include<queue>

using namespace std;

struct Compare		// Build custom compare operator to sort different way each other.
{							// [first는 내림차순, second는 오름차순.]	
	const bool operator()(pair<double, int> const &a, pair<double, int> const &b) const 
	{
		return a.first < b.first || (a.first == b.first && a.second > b.second);
	}
};


double Failure(int level, vector<int> stages)		// To figure out the failure rates.
{
	double cnt_now = 0, cnt_clear = 0;		// Count variables.
	for (int i = 0; i < stages.size(); i++)
	{	
		if (stages[i] >= level)						// The number of successor.
		{													// [해당 level complete 사람 수.]
			cnt_clear++;
			if (stages[i] == level)					// The number of failure.
				cnt_now++;								// [해당 level에 머무르고 있는(not complete) 사람 수.]		

		}
	}
	if (cnt_now == 0)									// The number of anyone exists.
		return 0;											// [해당 level에 존재하는 사람 X.]
	else
		return cnt_now / cnt_clear;				// The failure rates.
}

vector<int> solution(int N, vector<int> stages)			// To figure out levels which have high failure rates.
{
	vector<int> answer;								// The defined format as output.
	answer.resize(N);
	
	priority_queue<pair<double, int>, vector<pair<double, int>>, Compare>que;		// To avoid using sort again.
	for (int i = 0; i < answer.size(); i++)																// [Priority queue를 이용해서, sort function을 skip.]
		que.push({ Failure(i + 1, stages), i + 1 });

	int i = 0;
	while (!que.empty())
	{
		answer[i++] = que.top().second;		// [실패율이 높은 level을 내림차순으로 저장.]
		que.pop();
	}

	return answer;
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	int N = 5;
	vector<int>stages = { 2, 1, 2, 6, 2, 4, 3, 3};		// Input data and type.

	vector<int>failure_rate;						// Output data and type.
	failure_rate = 	solution(N, stages);		// Solution method with input data as parameters.

	for (int i = 0; i < failure_rate.size(); i++)		// Result.
		cout << failure_rate[i] << " ";
	cout << endl;
}