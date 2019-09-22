#include<iostream>
#include<algorithm>

#define INF 1000000001

using namespace std;

long long A, B, V;		// A = The height to climb.			B = The height to dismount.			V = The target height to arrive.

long long Binary()		// To figure out the time to arrive at summit.
{
	long long lf = 0, rt = V / (A - B) + 1;		// From minimum day to maximum day to arrive.
	long long day = INF;		// The day to spend.
	while (lf <= rt)			// Base case. [left couldn't go over the middle or right one.]
	{
		long long mid = (lf + rt) / 2;		// The day of spend.	
		if (V <= mid * (A - B) + A)		// [Day * (A-B) = climbed height.] + [ A = The last day's climb.]
		{
			day = min(day, mid + 1);		// To consider the last day climbed. 
			rt = mid - 1;	// To check if there is shorter day to arrive at summit.
		}
		else					// It's short of getting summit.
			lf = mid + 1;
	}
	return day;		// The minimum day to arrive at summit.
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> A >> B >> V;			// Input.
	cout << Binary() << endl;		// Output.
}