#include<iostream>
#include <vector>
#include<algorithm>

using namespace std;

bool comp(pair<int, int> const &a, pair<int, int> const &b)		// To do sort time as ascending order.
{																						// [(idx,time)을 time 기준 오름 차순으로 정렬.]
	return a.second < b.second;
}

int solution(vector<int> food_times, long long k)		// To figure out the efficient way to check circular data structure.
{
	int answer = 0;
	vector<pair<int, int>> vc;							// Temporary memory to store original input data.

	for (int i = 0; i < food_times.size(); i++)		// Set the data as (idx, time) format.
		vc.push_back(make_pair(i + 1, food_times[i]));

	sort(vc.begin(), vc.end(), comp);				// Ascending order of time. [Pair의 second 기준 오름 차순 정렬.] 
	
	int size = food_times.size();						// The total size of original input data.
	int prev = 0;											// Temporary memory to set previous minimum time.
	for (vector<pair<int, int>>::iterator idx = vc.begin(); idx != vc.end(); idx++, size--)
	{
		long long time = (long long)(idx->second - prev)*size;	// The calculation of data's total time.
								// [현재(idx)의 최소 시간 * 남은 크기의 size 계산을 하기 위해, 이전 과정의 최소 시간을 빼준다.]
		if (time == 0)		// The case of same time.
			continue;		// [동일한 food 시간을 가진 경우, 현재(idx)-이전(prev) = 0이 될 수 있다.]

		if (time <= k)		// The calculation of total time of input.
		{
			k -= time;
			prev = idx->second;	// Set the previous time to calculate this minimum time from others.
		}
		else
		{
			k %= size;		// [남은 k의 시간은, vc의 전체 사이즈보다 작기 때문에 남은 vc 공간 중 k번째의 index를 찾으면 된다.]
			sort(idx, vc.end());		// [남은 vc 중에서 index 기준으로 sorting을 다시 해야 한다. 순서대로 k번째의 index를 찾기 위해서.]
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