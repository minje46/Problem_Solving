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
		{							// [Interview에서 더 높은 순위를 가진 경우, recruit.]
			answer++;			// [Document score로 asceding sort를 했기 때문에, interview's score만이 비교 기준.]	
			rank = score[i].second;		// [최근에, 채용한 사람이 새로운 비교 기준이 되어야 한다.]
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