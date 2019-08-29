#include<iostream>
#include<algorithm>

#define MAX 16

using namespace std;

int N;					// N = The number of days to resignation.
int time[MAX];	// time = The memory of time to do consult.
int pay[MAX];		// pay = The memory of rewards after consult.
int answer = 0;	// answer = The maximum paycheck as output.

void DFS(int idx, int tot)		// To figure out the maximum paycheck.
{
	if (idx > N + 1)		// Base case. [The day of resignation.]
		return;	

	answer = max(answer, tot);		// Compare the maximum paycheck.

	for (int i = idx; i <= N; i++)		// Time flows. [After now, search the all cases.]
	{
		if (i == 0)			// To do dfs.	
			continue;		// [To avoid wrong index calculation.]
		
		DFS(i + time[i], tot + pay[i]);		// DFS.
	}
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> N;
	for (int i = 1; i <= N; i++)
		cin >> time[i] >> pay[i];		// Input.

	DFS(0, 0);								// DFS.	

	cout << answer << endl;			// Output.
}