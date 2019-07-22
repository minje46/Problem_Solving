#include<iostream>
#include<algorithm>
#include<vector>
//#pragma warning(disable:4996)

using namespace std;

int main()
{
	int T, test_case;
	//freopen("input_1.txt", "r", stdin);				// To load the test case as text file to do debug easily.
	cin >> T;						// T = The number of test case.
	for (test_case = 0; test_case < T; test_case++)
	{
		int N, K;						// N = The number of players.		K = The minimum gap players are able to stand taking bus together.
		cin >> N >> K;

		vector<int> player;		// player = The memory of players skills.
		for (int i = 1; i <= N; i++)
		{
			int cost;
			cin >> cost;
			player.push_back(cost);
		}

		sort(player.begin(), player.end());		// Ascending sort.
		int Answer = 1;			// Answer = The number of buses.
		for (int i = 1; i < N; i++)
		{								// [It's based on greedy algorithm.]		
// [index controlling 할 때, [i-answer]는 현재 가장 낮은 skill을 가진 player가 타고 있는 bus를 의미하기에, 최저 값을 가진 버스의 player와 비교 한 번만 하면 된다.]
			if (player[i] - player[i - Answer] <= K)		// [비교해야할 next player를 [i-answer]의 index controlling을 통해 각 버스에 존재하는 
				Answer++;											// 최고 level을 가진 선수와 비교하면 해당 버스에 타고있는 이전의 선수들은 비교를 skip해도 된다.]
		}																// [That's because it was sorted as ascneding before.]
			
		cout << "Case #" << test_case + 1 << endl;
		cout << Answer << endl;
	}

	return 0;
}