#include<iostream>
#include<string>
#include<vector>
#pragma warning(disable:4996)

#define MAX 8

using namespace std;

int N;								// N = The size of map.
int map[MAX][MAX];		// map = The memory of input data.
vector<string> vc[MAX];	// vc = The memory of rotated array.

void Simulation()			// To rotate matrix.
{
	for (int j = 0; j < N; j++)	// 90 degree.
	{
		string str;
		for (int i = N - 1; i >= 0; i--)
			str += to_string(map[i][j]);
		
		vc[j].push_back(str);
	}

	int idx = 0;
	for (int i = N - 1; i >= 0; i--)		// 180 degree.
	{
		string str;
		for (int j = N - 1; j >= 0; j--)
			str += to_string(map[i][j]);

		vc[idx++].push_back(str);
	}

	idx = 0;
	for (int j = N - 1; j >= 0; j--)		// 270 degree.
	{
		string str;
		for (int i = 0; i < N; i++)
			str += to_string(map[i][j]);

		vc[idx++].push_back(str);
	}
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);	cout.tie(0);

	//freopen("input.txt", "r", stdin);
	int test_case;
	cin >> test_case;
	for (int t = 1; t <= test_case; t++)
	{	
		cin >> N;
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
				cin >> map[i][j];			// Input data.
		}

		Simulation();		// Do rotate 90, 180 and 270 degree with matrix.

		cout << "#" << t << endl;
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < vc[i].size(); j++)
				cout << vc[i][j] << " ";		// Output.
			cout << endl;
			vc[i].clear();		// Initialization.
		}
	}
}