#include<iostream>
#include<algorithm>
#include<vector>
// 더하기 와 곱하기 연산 후, 큰 값 찾기.
using namespace std;

int  solution(vector<int>a, vector<int>b)
{
	if (a[0] % 2 == 2 || a[1] % 2 == 1 || a[0] + 1 != a[1])		// Wrong input.
		return -1;
	if (b[0] % 2 == 2 || b[1] % 2 == 1 || b[0] + 1 != b[1])		// Not sequence.
		return -1;

	int lf = -1, rt = -1;
	for (int i = 0; i < 2; i++)
	{
		int res_a = 0, res_b = 0;
		int tmp_a = a[i], tmp_b = b[i];
		for (int r = 100; r >= 1; r /= 10)		// Addition.
		{
			res_a += tmp_a / r;		// Each digit.
			tmp_a %= r;			

			res_b += tmp_b / r;		// Addition.
			tmp_b %= r;
		}
		lf = max(lf, res_a);
		rt = max(rt, res_b);
	}

	for (int i = 0; i < 2; i++)
	{
		int res_a = 1, res_b = 1;
		int tmp_a = a[i], tmp_b = b[i];
		for (int r = 100; r >= 1; r /= 10)		// Multiplication.
		{
			if (tmp_a / r > 0)				// Check the valid or not.
				res_a *= tmp_a / r;		// Each digit.
			tmp_a %= r;					
			
			if (tmp_b / r > 0)
				res_b *= tmp_b / r;		// Mulitplication.
			tmp_b %= r;
		}
		lf = max(lf, res_a);
		rt = max(rt, res_b);
	}

	if (lf > rt)
		return 1;			// Pobi win.
	else if (lf < rt)
		return 2;			// Crong win.
	else if (lf == rt)
		return 0;			// Draw.
	else
		return -1;		// Wrong.
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);	cout.tie(0);

	vector<int> pobi;			// The first input data.
	pobi.push_back(99);	pobi.push_back(102);
	vector<int> crong;		// The second input data.
	crong.push_back(211);	crong.push_back(212);

	cout << solution(pobi, crong) << endl;
}