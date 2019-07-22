#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

vector<pair<int, int>>score;			// The memory of document and interview's rank.

int Recruit()					// To figure out the maximum employees to recruit.
{	
	int answer = 1;			// answer = The number of recruits.
	int rank = score[0].second;		// rank = The rank of interviewee's score.

	for (int i = 1; i < score.size(); i++)
	{
		if (score[i].second < rank)		// It means that person who has lower rank of document score though, he has higher rank of interview's score.
		{							// [Interview���� �� ���� ������ ���� ���, recruit.]
			answer++;			// [Document score�� asceding sort�� �߱� ������, interview's score���� �� ����.]	
			rank = score[i].second;		// [�ֱٿ�, ä���� ����� ���ο� �� ������ �Ǿ�� �Ѵ�.]
		}
	}

	return answer;
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	int T;			// T = The number of test case.
	cin >> T;
	while (T--)
	{
		score.clear();
		int N;		// N = The number of employees.
		cin >> N;
		for (int i = 0; i < N; i++)
		{	
			int a, b;			// a = The rank of document score.		b = The rank of interview score.
			cin >> a >> b;
			score.push_back(make_pair(a, b));
		}

		sort(score.begin(), score.end());		// Ascending order.

		cout << Recruit() << endl;
	}
}