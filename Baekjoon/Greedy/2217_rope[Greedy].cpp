#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

vector<long long> rope;

int Max_rope(int N)
{
	long long max_avg = 0;

	for (int i = 0; i < rope.size(); i++)								 // The average max weight can't be larger than min weight that's because it uses only min weight.
		max_avg = max(max_avg, rope[i] * (i + 1));			// (Max weight + min weight) / N 이 min weight보다 크더라도 최대 허용 
																	   // 무게는 min weight보다 작아야 하기 때문에, 각 rope의 최저 무게만	
	return max_avg;												  // 고려해서 계산 하는 것이다.
}

int main(void)
{
	std::ios_base::sync_with_stdio(false);

	int N, weight;								// N = The number of rope.		weight = The max weight of rope to hold out.
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		cin >> weight;
		rope.push_back(weight);
	}	

	sort(rope.begin(), rope.end(), greater<int>());		// Sort with max weight of rope.
																// (각 rope는 최저 무게를 초과해서 버틸 수 없기 때문에, 최저 무게만	
	cout << Max_rope(N) << endl;						//	고려해서 계산을 할 수 있는 것.)
}