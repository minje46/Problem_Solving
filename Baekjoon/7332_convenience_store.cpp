#include<iostream>
#include<algorithm>
#include<memory.h>
#include<vector>

#define DAY 24
#define INF 987654321

using namespace std;

int N, answer;
int time[DAY];
vector<int> vc;
bool visit[1000];

bool Check(int arr[])
{
	for (int i = 0; i < DAY; i++)
	{
		if (arr[i] == 1)
			return false;
	}
	return true;
}

void DFS(int arr[], int cnt)
{
	if (Check(arr))
	{
		answer = min(answer, cnt);
		return;
	}
	
	for (int i = 0; i < vc.size(); i++)
	{
		if (!visit[i])
		{
			visit[i] = true;
			
			int tmp[DAY];
			memcpy(tmp, arr, sizeof(tmp));
			int idx = vc[i];
			for (int j = 0; j < 8; j++)
			{
				if (idx == 24)
					idx = 0;
				arr[idx++] -= 1;
			}

			DFS(arr, cnt+1);
			visit[i] = false;
			memcpy(arr, tmp, sizeof(tmp));
		}
	}

}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int test_case;
	cin >> test_case;
	while (test_case--)
	{
		memset(time, 0, sizeof(time));
		memset(visit, false, sizeof(visit));
		vc.clear();
		answer = INF;

		for (int i = 0; i < DAY; i++)
			cin >> time[i];

		cin >> N;
		for (int i = 0; i < N; i++)
		{
			int val;
			cin >> val;
			vc.push_back(val);
		}

		DFS(time, 0);

		if (answer == INF)
			cout << "No Solution" << endl;
		else
			cout << answer << endl;
	}
}