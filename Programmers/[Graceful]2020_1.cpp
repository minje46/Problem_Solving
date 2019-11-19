#include<iostream>
#include<algorithm>
#include<cmath>
#include<vector>

using namespace std;

double Dist(int ax, int ay, int bx, int by)
{
	return sqrt(pow((double)bx - ax, 2) + pow((double)by - ay, 2));
}

int solution(vector<int> restaurant, vector<vector<int>> riders, int k) 
{
	int answer = 0;
	for (int i = 0; i < riders.size(); i++)
	{
		if (Dist(restaurant[0], restaurant[1], riders[i][0], riders[i][1]) <= k)
			answer += 1;
	}

	return answer;
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);	cout.tie(0);

	vector<int> res = { 0,0 };
	vector<vector<int>>rd = {
		{-700,0},{150,180},{500,500},{150, -800},{800, 800},{-900, 500},{-1100, 900}
	};
	int k = 1000;

	cout << solution(res, rd, k) << endl;
}