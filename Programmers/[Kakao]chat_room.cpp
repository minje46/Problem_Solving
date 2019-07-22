// Open Kakao chatting room.
#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
#include<queue>
#include<map>

using namespace std;

vector<string> solution(vector<string> record)		// To manage open chatting room with user data.
{
	vector<string> answer;						// Output data type.			
	queue<pair<string, string>> que;		// To store instruction and user id.
	map<string, string> m;					// To store user id as a key and name as a value.
			// [Queue와 Map을 나눠서 user data를 저장함으로써, map을 통해 고유한 id의 변경된 name을 자동 관리 가능하다.]
	for (int i = 0; i < record.size(); i++)		// Each instruction.
	{		
		string str;				// Temporary string variable.
		vector<string> vc;	// Temporary vector memory to store each strings.
		for (int j = 0; j < record[i].size(); j++)
		{									// From 0 to end of string.		
			if (record[i][j] == ' ')	// Split point is blank. [공백 기준으로 split.]
			{
				vc.push_back(str);	// [공백으로 split된 string을 vector에 저장.]
				str.clear();				// Initialize temporary string variable to reuse.
			}
			else							// [공백이전까지는 string에 계속 저장.(이어	붙이기.)]
				str.push_back(record[i][j]);	// [String이 아니라, character여서 append가 불가능.]
		}
		vc.push_back(str);			// ['\n'기준, 마지막 name은 ' ' 에 걸리지 않기에, vector에 마지막 string 수동 저장.]

		if (vc[0] == "Change")		// The first case of changing user name, it just stores new name with userid.
			m[vc[1]] = vc[2];		// [Map 자료구조를 사용하였기 때문에, id가 기존에 있다면, 새로운 name으로 자동 update된다.] 
		else if (vc[0] == "Leave")	
			que.push(make_pair(vc[0], vc[1]));		// [Leave의 경우, 별다른 처리 없이 queue에 명령어와 id 저장.]
		else
		{									// The second case of changing user name.
			que.push(make_pair(vc[0], vc[1]));	// [User name을 변경할 수 있는 두 번째 방법이지만, eneter 될 때마다 map에 저장한다면
			m[vc[1]] = vc[2];		// 기존에 user id가 존재하는지 확인할 필요 없이 map 자료구조가 자동으로 update or store한다.]
		}
	}

	while (!que.empty())		// Queue has every pair of instruction and user id.
	{									// So it will be replaced as result format.
		string result;				
		auto cur = que.front();	
		que.pop();

		if (cur.first == "Enter")			// Queue has only two instructions such as "Enter" and "Leave".
			result = m[cur.second] + "님이 들어왔습니다.";
		else
			result = m[cur.second] + "님이 나갔습니다.";
		
		answer.push_back(result);
	}
	return answer;
}

int main(void)
{
	ios_base::sync_with_stdio(false);		// Input data.
	vector<string>record = {"Enter uid1234 Muzi", "Enter uid4567 Prodo","Leave uid1234","Enter uid1234 Prodo","Change uid4567 Ryan"};	
		
	vector<string>answer = solution(record);	// Output data.
	for (int i = 0; i < answer.size(); i++)
		cout << answer[i] << endl;
}