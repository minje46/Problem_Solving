#include<iostream>
#include<vector>

#define MAX 51

using namespace std;

int N, M;				// N = The size of circular queue.				M = The number of values to pop.
vector<int> que;	// que = The memory of input array as queue.

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> N >> M;
	for (int i = 1; i <= N; i++)
		que.push_back(i);			// Base input.

	int answer = 0;		// The total number of movement.
	for (int i = 0; i < M; i++)
	{	
		int val;
		cin >> val;			// The value to find.
		
		if (que[0] == val)	// Front.
		{
			que.erase(que.begin());	// Pop.
			continue;
		}

		int r_move = 0;	
		for (int i = 0; i < que.size(); i++)	
		{
			if (que[i] == val)		// From head to value.
				break;
			r_move += 1;
		}
		int l_move = que.size() - r_move;		// From tail to value.

		
		vector<int> tmp;
		if (r_move > l_move)	
		{
			int idx = que.size() - l_move;
			for (int i = idx+1; i < que.size(); i++)	// From the location of value to tail. 
				tmp.push_back(que[i]);
			for (int i = 0; i < idx; i++)					// From head to location of value.
				tmp.push_back(que[i]);
			answer += l_move;
		}
		else
		{
			for (int i = r_move + 1; i < que.size(); i++)		// From head to the location of value.
				tmp.push_back(que[i]);
			for (int i = 0; i < r_move; i++)						// From the location of value to head.
				tmp.push_back(que[i]);
			answer += r_move;
		}
		que.clear();		// Initialization.
		que = tmp;			// Swap.
	}
	cout << answer << endl;		// Output.
}