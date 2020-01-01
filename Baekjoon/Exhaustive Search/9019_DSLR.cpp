#include<iostream>
#include<memory.h>
#include<queue>
#include<string>

#define MAX 10001

using namespace std;

int A, B;							// A = The initial integer value.				B = The target integer value.
bool visit[MAX];				// visit = The memory of visited or not.
string answer;					// answer = The minimum combination to shot the target.

void BFS()						// To figure out the target number based on "DSLR" calculation.
{		
	queue<pair<int, string>> que;		// Basic step.
	que.push(make_pair(A, ""));
	visit[A] = true;

	while (!que.empty())
	{
		auto cur = que.front();
		que.pop();

		if (cur.first == B)						// Base case.
		{
			answer = cur.second;
			return;
		}

		int nval[4];			// nval = The memory of new value which will be calculated.
		nval[0] = (cur.first * 2) % 10000;										// "D" calculation.
		nval[1] = (cur.first - 1) < 0 ? 9999 : cur.first - 1;				// "S" calculation.
		nval[2] = (cur.first % 1000) * 10 + (cur.first / 1000);			// "L" calculation.
		nval[3] = (cur.first % 10) * 1000 + (cur.first / 10);				// "R" calculation.
		
		for (int i = 0; i < 4; i++)
		{
			if (!visit[nval[i]])			// Not visited yet.
			{
				string tmp = cur.second;
				if (i == 0)				// Key point!
					tmp += "D";		// When the string was copied, it takes lots of time.	
				else if (i == 1)
					tmp += "S";
				else if (i == 2)
					tmp += "L";
				else
					tmp += "R";

				que.push(make_pair(nval[i], tmp));
				visit[nval[i]] = true;
			}
		}
	}
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);	cout.tie(0);

	int test_case;
	cin >> test_case;
	for (int t = 1; t <= test_case; t++)
	{	// Initialization.
		memset(visit, false, sizeof(visit));
		answer = "";
			
		cin >> A >> B;								// Input.
		
		BFS();											// Exhaustive search.

		cout << answer << endl;					// Output.
	}
}