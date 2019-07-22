#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

vector<pair<int, int>> meeting;								// meeting = All time table of meetings.

int Reserve_meeting()
{
	vector<pair<int, int>> reservation;						// reservation = Real time table of meetings.

	reservation.push_back(meeting[0]);						// The first one can be the greedy value that's because it is already sorted in end time.
	for (int i = 1, j = 0; i < meeting.size(); i++)				// (End time만 가지고 greedy를 비교할 수 있기때문에, 첫번째 것을 바로 사용할 수 있다.)
	{
		if (reservation[j].second <= meeting[i].first)		// The next meeting should start after previous meeting finished.
		{
			reservation.push_back(meeting[i]);
			j++;
		}
	}
	return reservation.size();
}

bool compare(const pair<int,int>&a, const pair<int,int>&b)
{
	if (a.second == b.second)
		return a.first < b.first;
	
	return a.second < b.second;
}

int main(void)
{
	std::ios_base::sync_with_stdio(false);

	int N, start, end;								// N = The number of meeting.   start = Start time of meeting.    end =  End time of meeting.
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		cin >> start >> end;
		meeting.push_back({ start, end });
	}

	sort(meeting.begin(), meeting.end(), compare);		// Sort with end time. 
																	// (End time으로 sort하는 이유는, end-start의 term이 가장 짧은 meeting 중에서 빠른 시간에
																	// 시작하는 meeting을 구분하기 위해 start time이 늦어지는 만큼 가중치를 줄 경우,
	cout << Reserve_meeting() << endl;					// term = end time - start time + start time 이 되기 때문에 end time만 가지고 sort해도 된다.)
}