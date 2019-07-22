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
// [index controlling �� ��, [i-answer]�� ���� ���� ���� skill�� ���� player�� Ÿ�� �ִ� bus�� �ǹ��ϱ⿡, ���� ���� ���� ������ player�� �� �� ���� �ϸ� �ȴ�.]
			if (player[i] - player[i - Answer] <= K)		// [���ؾ��� next player�� [i-answer]�� index controlling�� ���� �� ������ �����ϴ� 
				Answer++;											// �ְ� level�� ���� ������ ���ϸ� �ش� ������ Ÿ���ִ� ������ �������� �񱳸� skip�ص� �ȴ�.]
		}																// [That's because it was sorted as ascneding before.]
			
		cout << "Case #" << test_case + 1 << endl;
		cout << Answer << endl;
	}

	return 0;
}