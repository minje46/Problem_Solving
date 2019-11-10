#include<iostream>
#include<vector>

#define MAX 101

using namespace std;

int solution(vector<int> priorities, int location)		//	 Printer based on priority queue.
{
	int cnt = 1;
	vector<int>que;
	for (int i = 0; i < priorities.size(); i++)
		que.push_back(i);		// Base state.

	while (!que.empty())
	{
		auto cur = que[0];		// First one.
		
		bool flag = false;
		for (int i = 1; i < que.size(); i++)
		{
			if (priorities[cur] < priorities[que[i]])		// Compare the priority.
			{
				que.push_back(cur);			// If there is higher one, push again.
				que.erase(que.begin());
				flag = true;
				break;
			}
		}
		if (flag)
			continue;

		if (location == que[0])			// Target.
			break;
		que.erase(que.begin());
		cnt += 1;
	}
	return cnt;
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);	cout.tie(0);

//	vector<int> priorities = { 2, 1, 3, 2 };
	vector<int> priorities = { 1, 1, 9, 1, 1, 1 };
	cout << solution(priorities, 0) << endl;
}