#include<iostream>
#include<algorithm>
#include<memory.h>
#include<vector>
#include<queue>
//#pragma warning(disable:4996)

#define MAX_S 10
#define MAX_C 1001

using namespace std;

int N, M, K;		// N = The number of receptions.			M = The number of repair shops.			K = The number of customer.
int reception[MAX_S], repair[MAX_S], customer[MAX_C];		// The memory of reception and repair shop's lead time.
vector<pair<int, int>> take_rec(MAX_S), take_rep(MAX_S);		// The memory of reception and repair lines people are using now.
queue<int> wait_rec, wait_rep;		// The waiting queue memory for reception and repair lines.
int A, B;				// A = The reception number specific customer used.		B = The repair shop number specific customer used.
int answer = 0;	

void Car_center()		// The flow of car_center working.
{
	int time = 0, fin_num = 0;		// time = The total time.		fin_num = The count of finished people.
	vector<int> used_rec, used_rep;		// Check the specific customer's data.

	while (fin_num < K)		// Untill the whole of customers are taking car center service.
	{
		for (int i = 1; i <= K; i++)		// The whole of customers.
		{
			if (customer[i] == time)	// The customer arrived on time.
				wait_rec.push(i);			// It was dealt with reception waiting queue.	
		}

		for (int i = 1; i <= N; i++)		// The whole of receptions.
		{
			if (take_rec[i].first != 0 && take_rec[i].second == time)		// Using recption + Time limits.
			{
				wait_rep.push(take_rec[i].first);	// It was dealt with repair waiting queue.
				take_rec[i].first = 0;	// Initialize.
			}
		}

		for (int i = 1; i <= N; i++)		// The whole of receptions.
		{
			if (wait_rec.empty())		// If there is no customer waits for reception services,
				break;						// break.
			if (take_rec[i].first == 0)	// The case of not used now.
			{
				take_rec[i].first = wait_rec.front();		// Write down the customer's index.
				take_rec[i].second = time + reception[i];		// The finish time.
				wait_rec.pop();		// Delete from waiting queue.

				if (i == A)		// Special condition.
					used_rec.push_back(take_rec[i].first);
			}
		}

		for (int i = 1; i <= M; i++)		// The whole of repair lines.
		{
			if (take_rep[i].first != 0 && take_rep[i].second == time)	// Using repair line + Time limits.
			{
				take_rep[i].first = 0;	// Initialize.
				fin_num++;					// Count the finished customer.
			}
		}


		for (int i = 1; i <= M; i++)
		{
			if (wait_rep.empty())		// If there is no customer waits for reception services,
				break;						// break.
			if (take_rep[i].first == 0)	// The case of not used now.
			{
				take_rep[i].first = wait_rep.front();		// Write down the customer's index.
				take_rep[i].second = time + repair[i];		// The finish time.
				wait_rep.pop();		// Delete from waiting queue.

				if (i == B)		// Special condition.
					used_rep.push_back(take_rep[i].first);
			}
		}
		time++;		// Time flows.
	}

	for (int i = 0; i < used_rec.size(); i++)		// From special A condition.
	{
		for (int j = 0; j < used_rep.size(); j++)		// To special B condition.
		{
			if (used_rec[i] == used_rep[j])		// If both conditions meet, 
			{
				answer += used_rec[i];			// count.
				break;
			}
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
		memset(reception, 0, sizeof(reception));
		memset(repair, 0, sizeof(repair));
		memset(customer, 0, sizeof(customer));
		answer = 0;

		cin >> N >> M >> K >> A >> B;
		for (int i = 1; i <= N; i++)			// Input of reception's time to deal with.
			cin >> reception[i];
		for (int i = 1; i <= M; i++)			// Input of repair shop's time to deal with.
			cin >> repair[i];
		for (int i = 1; i <= K; i++)			// Input of customer's arrived time.
			cin >> customer[i];

		Car_center();			// To take car center services.

		if (answer == 0)		// There is no case to fit special conditions.
			cout << "#" << t << " " << -1 << endl;
		else
			cout << "#" << t << " " << answer << endl;
	}
}