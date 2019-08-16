#include<iostream>
#include<algorithm>
#include<memory.h>
#include<vector>
//#pragma warning(disable:4996)

#define MAX 11
#define INF 987654321

using	namespace std;

int N, answer = INF;			// N = The size of map.		K = The number of total people.		answer = The minimum total time to move as output.
int map[MAX][MAX];		// map = The memory of original map data.
int order[MAX];				// order = The memory of which person takes stair.	[�� ���� stair�� �����ߴ���, ����.]
vector<pair<int, int>> person, stair;		// The memory of each location.

int Move()		// To figure out the total time to move.
{
	int time = 0, A = 0, B = 0;		// time = The total time to move.		A,B = The number of people take each stair.
	int move_A[MAX], move_B[MAX];		// move_A,_B = The memory of distance time to arrive stair.
	for (int i = 0; i < person.size(); i++)
	{
		if (order[i] == 0)		// The case of first stair.
			move_A[A++] = abs(stair[0].first - person[i].first) + abs(stair[0].second - person[i].second);

		if (order[i] == 1)		// The case of second stair.
			move_B[B++] = abs(stair[1].first - person[i].first) + abs(stair[1].second - person[i].second);
	}
	sort(move_A, move_A + A);		// As early as people arrive.
	sort(move_B, move_B + B);		// [���� ������ ������� ��� �������� ���� ����.] 

	int n_a = 0, n_b = 0;	// n_a,_b = The index of people couldn't arrive yet. [���� �������� ���ϰų�, ������� people�� index.]
	vector<int> stair_A, stair_B;		// The memory of stair which people are taking now. [���� stair �̿����� ����� �̵� �ð�.]
	while (n_a != A || n_b != B || !stair_A.empty() || !stair_B.empty())		// [������� �̵����� ��� + ��� �������� �ִ� ���.]
	{
		for (int i = n_a; i < A; i++)		
		{
			if (move_A[i] <= 0)
			{
				if (stair_A.size() < 3)
				{
					stair_A.push_back(map[stair[0].first][stair[0].second] + 1 + move_A[i]);		// It is for waiting time of stair.
					n_a++;		// It doesn't need to check again, after arrived people.
				}
				else
					move_A[i] = 0;		// [If there is no enough space to use stair.]
			}
		}
		for (int i = n_b; i < B; i++)
		{
			if (move_B[i] <= 0)
			{
				if (stair_B.size() < 3)
				{
					stair_B.push_back(map[stair[1].first][stair[1].second] + 1 + move_B[i]);		// [���ð� ���θ� move_A[]�� �̿��Ͽ� ���.]
					n_b++;		// [�̹� ��� ������ ����� index ������ ����, �������� �˻�X.]
				}
				else
					move_B[i] = 0;		// [�̹� ��ܿ� ����������, full�� ���, ���ð��� �ʿ� ���� ����.]
			}
		}

		for (int i = 0; i < stair_A.size(); i++)		// The time for going down stair.
			stair_A[i] -= 1;

		for (int i = 0; i < stair_B.size(); i++)		// [��� �̿����� �ð�.]
			stair_B[i] -= 1;

		sort(stair_A.begin(), stair_A.end(), greater<int>());		// To delete finished people.
		sort(stair_B.begin(), stair_B.end(), greater<int>());		// [��� �̿��� ���� ������� ����� ����.]

		for (int i = stair_A.size() - 1; i >= 0; i--)		// To check whether it was finished or not from last index.
		{
			if (stair_A[i] == 0)
				stair_A.pop_back();
		}

		for (int i = stair_B.size() - 1; i >= 0; i--)		// [vector�� �̿��ؼ�, pop�� �ϸ鼭, index ���̴� ���� �����ϱ� ����.]
		{
			if (stair_B[i] == 0)
				stair_B.pop_back();
		}

		for (int i = n_a; i < A; i++)		// Decrease the moving time as time flows.
			move_A[i] -= 1;
		for (int i = n_b; i < B; i++)		// [�ð� �帧�� ����, �̵��ð� ����.]
			move_B[i] -= 1;
		
		++time;		// Increase the total time one by one.
	}
	return time;
}

void DFS(int cnt)		// To do exhaustive search.
{
	if (cnt >= person.size())	// [��ü �ο����� index������ ������ ���.]
	{
		answer = min(answer, Move());
		return;
	}

	for (int i = 0; i < 2; i++)	// [Loop�� ����, ��� ����� ���� Ȯ���Ѵ�.]
	{
		order[cnt] = i;		// [�̿��� stair�� ��ȣ�� ������� ����.]
		DFS(cnt + 1);		
	}

}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);

//	freopen("input.txt", "r", stdin);

	int test_case;
	cin >> test_case;
	for (int t = 1; t <= test_case; t++)
	{	// Initialization.
		memset(map, 0, sizeof(map));
		person.clear();
		stair.clear();

		cin >> N;
		for (int i = 1; i <= N; i++)
		{
			for (int j = 1; j <= N; j++)
			{
				cin >> map[i][j];
				if (map[i][j] == 1)			// The location of person.
					person.push_back(make_pair(i, j));
				else if (map[i][j] > 1)		// The location of stairs.
					stair.push_back(make_pair(i, j));
			}
		}

		answer = INF;	
		DFS(0);		// To do exhaustive search.
			
		cout << "#" << t << " " << answer << endl;		// The shortest time to move as output.
	}
}
