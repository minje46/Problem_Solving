#include<iostream>
#include <vector>
#include<algorithm>

using namespace std;

bool comp(pair<int, int> const &a, pair<int, int> const &b)		// To do sort time as ascending order.
{																						// [(idx,time)�� time ���� ���� �������� ����.]
	return a.second < b.second;
}

int solution(vector<int> food_times, long long k)		// To figure out the efficient way to check circular data structure.
{
	int answer = 0;
	vector<pair<int, int>> vc;							// Temporary memory to store original input data.

	for (int i = 0; i < food_times.size(); i++)		// Set the data as (idx, time) format.
		vc.push_back(make_pair(i + 1, food_times[i]));

	sort(vc.begin(), vc.end(), comp);				// Ascending order of time. [Pair�� second ���� ���� ���� ����.] 
	
	int size = food_times.size();						// The total size of original input data.
	int prev = 0;											// Temporary memory to set previous minimum time.
	for (vector<pair<int, int>>::iterator idx = vc.begin(); idx != vc.end(); idx++, size--)
	{
		long long time = (long long)(idx->second - prev)*size;	// The calculation of data's total time.
								// [����(idx)�� �ּ� �ð� * ���� ũ���� size ����� �ϱ� ����, ���� ������ �ּ� �ð��� ���ش�.]
		if (time == 0)		// The case of same time.
			continue;		// [������ food �ð��� ���� ���, ����(idx)-����(prev) = 0�� �� �� �ִ�.]

		if (time <= k)		// The calculation of total time of input.
		{
			k -= time;
			prev = idx->second;	// Set the previous time to calculate this minimum time from others.
		}
		else
		{
			k %= size;		// [���� k�� �ð���, vc�� ��ü ������� �۱� ������ ���� vc ���� �� k��°�� index�� ã���� �ȴ�.]
			sort(idx, vc.end());		// [���� vc �߿��� index �������� sorting�� �ٽ� �ؾ� �Ѵ�. ������� k��°�� index�� ã�� ���ؼ�.]
			return (idx+k)->first;
		}
	}
	return -1;
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	vector<int> food_times = { 3, 1, 2 };
	int k = 5;

	cout << solution(food_times, k) << endl;
}