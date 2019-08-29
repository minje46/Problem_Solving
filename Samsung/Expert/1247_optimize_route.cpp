#include<iostream>
#include<algorithm>
#include<memory.h>
#include<vector>
//#pragma warning(disable:4996)

#define MAX 11
#define INF 987654321

using namespace std;

int N;							// N = The nubmer of customers.
pair<int, int> dst;			// dpt, dst = The location of departure and destination.
vector<pair<int, int>>customer;		// custiomer = The memory of customer's location.
bool visit[MAX];			// visit = The memory of visited or not.
int answer = INF;			// answer = The shortest way to arrive destination as output.

int Distance(int a, int b)		// To calculate the absolute distance between A and B.
{
	return abs(customer[a].first - customer[b].first) + abs(customer[a].second - customer[b].second);
}

void DFS(int idx, int cnt, int tot)			// To do exhaustive search for the shortest way.
{
	if (cnt == N)		// Base case. [Visited all customers.]
	{
		tot += (abs(customer[idx].first - dst.first) + abs(customer[idx].second - dst.second));		// To arrive destination.
		answer = min(answer, tot);		// Compare the shortest way.
		return;
	}

	if (idx > N)			// Base case. [Overflow.]
		return;

	for (int i = 1; i <= N; i++)		// To search all cases.
	{
		if (!visit[i])		// To avoid duplicated cases.
		{
			visit[i] = true;
			DFS(i, cnt + 1, tot + Distance(idx, i));
			visit[i] = false;
		}
	}
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	//freopen("input.txt", "r", stdin);

	int test_case;
	cin >> test_case; 
	for (int t = 1; t <= test_case; t++)
	{	// Initialization.
		customer.clear();
		memset(visit, false, sizeof(visit));
		answer = INF;

		cin >> N;
		for (int i = 0; i < N + 2; i++)
		{
			int a, b;
			cin >> a >> b;

			 if (i == 1)		// Destination.
			{
				dst.first = a;
				dst.second = b;
			}
			else				// Home + Customer's location.	
				customer.push_back(make_pair(a, b));
		}

		DFS(0, 0, 0);		// Simulation. [Permutation.]

		cout << "#" << t << " " << answer << endl;		// Output.
	}
}