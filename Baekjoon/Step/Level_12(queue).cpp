// 12 - 1 (Basic queue)
/*
#include<iostream>
#include<queue>
using namespace std;
*/

// 12 - 2

// 12 - 3
/*
#include<iostream>
#include<queue>
using namespace std;

int main(void)
{
	int T;							// T = test case.
	cin >> T;
	queue<int> result;			// result stores the location of files user asked.

	while (T-- > 0)
	{
		int N, M, temp, location=0;					// N = number of files.		M = location of files user want to know.	 
		queue<pair<int, int>> value;
		priority_queue<int> priority;	// Priority_queue should pop the highest priority of element inside queue.
											
		cin >> N >> M;
		for (int i = 0; i < N; i++)		// Type the priority of files.
		{
			cin >> temp;
			value.push({ i,temp });
			priority.push(temp);
		}	

		while (!value.empty())
		{
			int now_idx = value.front().first;
			int now_val = value.front().second;
			value.pop();

			if (now_val == priority.top())		// Compare the value is the highest priority or not.
			{
				priority.pop();					// It is the highest priority which is selected automatically by library function.
				location++;						// location means the index(location) of file user asked.
				if (now_idx == M)
				{
					result.push(location);
					location = 0;
					break;
				}
			}
			else									// The value was poped is not the highest priority, so it should push again at tail.
				value.push({ now_idx, now_val });
		}
	}

	while (!result.empty())
	{
		cout << result.front() << "\n";
		result.pop();
	}
}
*/

// 12 - 4
/*
#include<iostream>
#include<queue>

using namespace std;

int main(void)
{
	int N, M, cnt = 1;				// N = number of values.		M = position of kill		cnt = count for index.
	cin >> N >> M;

	queue<pair<int, int>> circular;		// pair_queue stores index and value together.	
	queue<int> sequence;				// sequence = result.

	for (int i = 0; i < N; i++)
		circular.push({ i, i + 1 });

	while (!circular.empty())
	{
		int now_idx = circular.front().first;
		int now_val = circular.front().second;
		circular.pop();
	
		if (M == cnt)			// Compare the index is correct to kill or not.
		{
			sequence.push(now_val);
			cnt = 1;
		}
		else
		{
			circular.push({ now_idx, now_val });
			cnt++;
		}
	}

	for(int i=0; i<N; i++)
	{
		if (i == 0)
			cout << "<";

		if (i == N - 1)
			break;

		cout << sequence.front() << ", ";
		sequence.pop();
		
	}
	cout << sequence.front() << ">";
	sequence.pop();
}	
*/

// 12 - 5

