#include<iostream>
#include<algorithm>
#include<cmath>

using namespace std;

int N, M, K;		// N = The number of girls.		M = The number of boys.		K = The number of students to do internship.

int Team()			// To figure out the number of team can organize.
{
	int total = N + M, cnt = 0;			// total = The sum of girls and boys.	
	while (total > K)			// The prior condition is arranging internship first. [Intern 학생 수를 최소한 확보해야 하기 때문.]
	{
		if (N < 2 || M < 1)	// The base case. [Team 구성을 위한 최소 조건.]
			break;
						// Make team.	
		N = N - 2;				
		M = M - 1;
		total = N + M;
		cnt++;
	}

	if (total < K)
		cnt--;

	return cnt;
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> N >> M >> K;

	cout << Team() << endl;			// The maximum number of team can be organized.
}