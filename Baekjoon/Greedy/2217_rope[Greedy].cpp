#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

vector<long long> rope;

int Max_rope(int N)
{
	long long max_avg = 0;

	for (int i = 0; i < rope.size(); i++)								 // The average max weight can't be larger than min weight that's because it uses only min weight.
		max_avg = max(max_avg, rope[i] * (i + 1));			// (Max weight + min weight) / N �� min weight���� ũ���� �ִ� ��� 
																	   // ���Դ� min weight���� �۾ƾ� �ϱ� ������, �� rope�� ���� ���Ը�	
	return max_avg;												  // ����ؼ� ��� �ϴ� ���̴�.
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
																// (�� rope�� ���� ���Ը� �ʰ��ؼ� ��ƿ �� ���� ������, ���� ���Ը�	
	cout << Max_rope(N) << endl;						//	����ؼ� ����� �� �� �ִ� ��.)
}