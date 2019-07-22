// Failure rate.
#include<iostream>
#include<algorithm>
#include <string>
#include <vector>
#include<queue>

using namespace std;

struct Compare		// Build custom compare operator to sort different way each other.
{							// [first�� ��������, second�� ��������.]	
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
		{													// [�ش� level complete ��� ��.]
			cnt_clear++;
			if (stages[i] == level)					// The number of failure.
				cnt_now++;								// [�ش� level�� �ӹ����� �ִ�(not complete) ��� ��.]		

		}
	}
	if (cnt_now == 0)									// The number of anyone exists.
		return 0;											// [�ش� level�� �����ϴ� ��� X.]
	else
		return cnt_now / cnt_clear;				// The failure rates.
}

vector<int> solution(int N, vector<int> stages)			// To figure out levels which have high failure rates.
{
	vector<int> answer;								// The defined format as output.
	answer.resize(N);
	
	priority_queue<pair<double, int>, vector<pair<double, int>>, Compare>que;		// To avoid using sort again.
	for (int i = 0; i < answer.size(); i++)																// [Priority queue�� �̿��ؼ�, sort function�� skip.]
		que.push({ Failure(i + 1, stages), i + 1 });

	int i = 0;
	while (!que.empty())
	{
		answer[i++] = que.top().second;		// [�������� ���� level�� ������������ ����.]
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