#include<iostream>
#include<algorithm>
#include<memory.h>
#include<vector>
#include<queue>
#include<stack>
#include<cmath>
//#pragma warning(disable:4996)

#define MAX_N 4
#define MAX_M 8
#define MAX_K 21

using namespace std;

int K;				// K = The number of rotation.
int magnet[MAX_N][MAX_M];		// magnet = The memory of magnet's data.
vector<pair<int, int>> rotation;		// rotation = The memory of rotation data which magnet should turn.
int answer = 0;							// answer = The total value of magnets as output.

int Score()		// To count the score of magnets.
{
	int tot = 0;
	for (int i = 0; i < MAX_N; i++)
	{
		if (magnet[i][0] == 1)		// Count the score, when the magnet[0] is "S".
			tot += pow(2, i);			// Each magnet has different scores.
	}
	return tot;
}

void CW(int idx)		// To rotate the magnet in clock wise.
{
	queue<int>que;	// FIFO.
	for (int i = 0; i < MAX_M; i++)
		que.push(magnet[idx][i]);		// The whole data of idx'th magnet.

	for (int i = 1; i < MAX_M; i++)
	{
		magnet[idx][i] = que.front();	// Right shift.
		que.pop();
	}
	magnet[idx][0] = que.front();		// To avoid overflow.
}

void CCW(int idx)	// To rotate the magnet in counther clock wise.
{
	stack<int>stk;		// FILO	
	for (int i = 0; i < MAX_M; i++)
		stk.push(magnet[idx][i]);		// The whole data of idx'th magnet.

	for (int i = MAX_M - 2; i >= 0; i--)
	{
		magnet[idx][i] = stk.top();		// Left shift.
		stk.pop();
	}
	magnet[idx][MAX_M - 1] = stk.top();	// To avoid underflow.
}

void Cycle()		// To compare each magnet has different state or not.
{
	for (int i = 0; i < K; i++)		// In the whole of roation.
	{
		vector<pair<int, int>> vc;			// vc = The temporary memory for data to rotate.
		int idx = rotation[i].first;			// idx = The magnet's number.
		int dir = rotation[i].second;		// dir = The direction of rotation.
		vc.push_back(make_pair(idx, dir));	// The current rotation.

		for (int lf = idx - 1; lf >= 0; lf--)		// LEFT.
		{
			if (magnet[lf][2] == magnet[lf + 1][6])	// If both are same state, additional rotation will not happen.
				break;
			
			dir *= -1;		// Because of opposite state, direction is opposite way as well.
			vc.push_back(make_pair(lf, dir));
		}

		dir = rotation[i].second;		// Initialize.
		for (int rt = idx + 1; rt < MAX_N; rt++)			// Right.
		{
			if (magnet[rt - 1][2] == magnet[rt][6])	// If both are same state, additional rotation will not happen.
				break;

			dir *= -1;		// Because of opposite state, direction is opposite way as well.
			vc.push_back(make_pair(rt, dir));
		}

		for (int k = 0; k < vc.size(); k++)		// In the whole of rotation from rotation[k].
		{
			if (vc[k].second == 1)		// CW.
				CW(vc[k].first);
			else								// CCW.
				CCW(vc[k].first);
		}
	}
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);

//	freopen("input.txt", "r", stdin);

	int test_case;
	cin >> test_case;
	for (int t = 1; t <= test_case; t++)
	{	// Initialization.
		memset(magnet, 0, sizeof(magnet));
		rotation.clear();
		answer = 0;

		cin >> K;
		for (int i = 0; i < MAX_N; i++)		// From 0-4.
		{
			for (int j = 0; j < MAX_M; j++)
				cin >> magnet[i][j];			// Input of magnet's data.
		}
		for (int i = 0; i < K; i++)			
		{
			int idx, dir;
			cin >> idx >> dir;						// Input of rotation's data.
			rotation.push_back(make_pair(idx-1, dir));
		}
		
		Cycle();			// Simulation.

		answer = Score();		// Count the score.
		cout << "#" << t << " " << answer << endl;		// Output.
	}
}