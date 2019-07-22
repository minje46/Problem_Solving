#include<iostream>
#include<cmath>
#define _USE_MATH_DEFINES
#define M_PI 3.14159265358979323846
#pragma warning(disable:4996)

using namespace std;

double Answer = 0;
double Distance(int R, int l, int r, int h)
{
	double dist = 0;

	if (h < R)
		dist = 2 * (R *acos((double)(R - h) / R) - sqrt(pow(R, 2) - pow(R - h, 2)));

	else
		dist = (2 * (h - (2 * R))) + R * M_PI;

	return dist;
}

int main(int argc, char** argv)
{
	ios_base::sync_with_stdio(false);
	int T, test_case;
	freopen("[scpc_pre1_2019]input_2.txt", "r", stdin);

	cin >> T;
	for (test_case = 0; test_case < T; test_case++)
	{
		int R, S, E, N;		// R = Radius.		S = Start.		E = End.	N = The number of obstacles.
		cin >> R >> S >> E >> N;

		Answer = E - S;		// Linear distance from start to end.
		for (int i = 0; i < N; i++)
		{
			int l, r, h;		// l = The left point.		r = The right point.		h = The height.
			cin >> l >> r >> h;

			Answer += Distance(R, l, r, h);
		}

		cout.setf(ios::fixed);
		cout.precision(10);	
		cout << "Case #" << test_case + 1 << endl;
		cout << Answer << endl;
	}
	return 0;
}