#include<iostream>
#include<algorithm>
#include<string>

using namespace std;

int main(void)
{
	ios_base::sync_with_stdio(false);

	string N;						// N = The positive number as input. 
	cin >> N;					// The N could be 10^5 as maximum, that's why the data type was used as string.

	long long sum = 0;		// sum = The total value of each digits.	

	for (int i = 0; i < N.size(); i++)	
		sum += (N[i]-'0');		// To figure out the total digit's sum could be divided as three.

	sort(N.begin(), N.end(), greater<char>());		// To show the biggest value as bigger as they can do combination.
	int last = N[N.size() - 1] - '0';		// [30의 배수가 되기 위한 조건 1 : 마지막 자릿 수가 0이 되어야 한다.]

	if (last != 0 || sum % 3)		// [30의 배수가 되기 위한 조건 2 : 모든 자릿 수의 합이 3의 배수이어야 한다.]
		cout << -1 << endl;

	else
		cout << N << endl;
}