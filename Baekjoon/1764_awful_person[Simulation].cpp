#include<iostream>
#include<algorithm>
#include<string>
#include<vector>

using namespace std;

vector<string> list;				// list = The memory of unheard people's list.
vector<string> answer;			// answer = The memory of unseen and unheard people list.

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int N, M;				// N = The number of unheard people.		M = The number of unseen people.
	cin >> N >> M;
	for (int i = 0; i < N; i++)
	{
		string st;
		cin >> st;		// Unheard people.
		list.push_back(st);
	}
	sort(list.begin(), list.end());		// Sort as dictionary order.

	for (int i = 0; i < M; i++)
	{
		string st;
		cin >> st;		// Unseen people.	
		
		if(binary_search(list.begin(), list.end(), st))			// Check the unseen person's name is listed on unheard people's list.
			answer.push_back(st);		// Unseen and unheard person.
	}

	sort(answer.begin(), answer.end());		// Sort again because of binary search. [Binary search라서, 찾은 결과 값은 사전식 order를 보장할 수 없다.]
	cout << answer.size() << endl;				
	for (int i = 0; i < answer.size(); i++)
		cout << answer[i] << endl;
}