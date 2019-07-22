#include<iostream>
#include<algorithm>
#include<vector>
#include<memory.h>

#define MAX 901

using namespace std;

int N, K, F;			//  N = The total number of kids.		K = The number of kids going to picnic.		F = The number of kid's relationship.
bool rs[MAX][MAX];			// rs = The memory of kid's relationship's data.
bool taken[MAX];			// raken = The memory for combinations.
bool flag = false;				// flag = It means whether answer is or not.

void Print()			// To print the answer which is the first combination based on conditions.
{
	for (int i = 1; i <= N; i++)
		if (taken[i])
			cout << i << endl;
}

bool promising(int new_friend)		// To figure out whether they are friends or not.
{
	for (int i = 1; i <= N; i++)
	{
		if (taken[i])		// The case of selected kids. [현재 선택된 것만 check하면 됨.]
			if (!rs[new_friend][i])		// The case they aren't friends.
				return false;
	}
	return true;
}

void Picnic(int idx, int cnt)		// To figure out the whole of cases making combinations.
{
	if (flag)				// The case that the answer was already found.
		return;

	if (cnt == K)		// The member are organized.
	{						// [K까지 조건이 맞춰진 조합의 경우.]
		flag = true;		// [처음으로 구성된 조건에 맞는 조합이 answer.]
		Print();
		return;
	}

	for (int i = idx + 1; i <= N; i++)
	{
		if (!promising(i))		// Check this kid is possible to join or not.
			continue;
		taken[i] = true;		
		Picnic(i, cnt + 1);	// Recursively make a combination.
		taken[i] = false;		// Based on back tracking.
	}
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> K >> N >> F;
	for (int i = 0; i < F; i++)
	{
		int a, b;
		cin >> a >> b;
		rs[a][b] = true;		// The relationship of friends.
		rs[b][a] = true;
	}

	for (int i = 1; i <= N; i++)
	{
		if (!flag)			// If the combination was not found yet, keep searching other combinations.
		{
			taken[i] = true;
			Picnic(i, 1);
			taken[i] = false;
		}
	}

	if (!flag)				// The case of failure making party.
		cout << -1 << endl;
}