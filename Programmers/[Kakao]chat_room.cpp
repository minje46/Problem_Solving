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
			// [Queue�� Map�� ������ user data�� ���������ν�, map�� ���� ������ id�� ����� name�� �ڵ� ���� �����ϴ�.]
	for (int i = 0; i < record.size(); i++)		// Each instruction.
	{		
		string str;				// Temporary string variable.
		vector<string> vc;	// Temporary vector memory to store each strings.
		for (int j = 0; j < record[i].size(); j++)
		{									// From 0 to end of string.		
			if (record[i][j] == ' ')	// Split point is blank. [���� �������� split.]
			{
				vc.push_back(str);	// [�������� split�� string�� vector�� ����.]
				str.clear();				// Initialize temporary string variable to reuse.
			}
			else							// [�������������� string�� ��� ����.(�̾�	���̱�.)]
				str.push_back(record[i][j]);	// [String�� �ƴ϶�, character���� append�� �Ұ���.]
		}
		vc.push_back(str);			// ['\n'����, ������ name�� ' ' �� �ɸ��� �ʱ⿡, vector�� ������ string ���� ����.]

		if (vc[0] == "Change")		// The first case of changing user name, it just stores new name with userid.
			m[vc[1]] = vc[2];		// [Map �ڷᱸ���� ����Ͽ��� ������, id�� ������ �ִٸ�, ���ο� name���� �ڵ� update�ȴ�.] 
		else if (vc[0] == "Leave")	
			que.push(make_pair(vc[0], vc[1]));		// [Leave�� ���, ���ٸ� ó�� ���� queue�� ��ɾ�� id ����.]
		else
		{									// The second case of changing user name.
			que.push(make_pair(vc[0], vc[1]));	// [User name�� ������ �� �ִ� �� ��° ���������, eneter �� ������ map�� �����Ѵٸ�
			m[vc[1]] = vc[2];		// ������ user id�� �����ϴ��� Ȯ���� �ʿ� ���� map �ڷᱸ���� �ڵ����� update or store�Ѵ�.]
		}
	}

	while (!que.empty())		// Queue has every pair of instruction and user id.
	{									// So it will be replaced as result format.
		string result;				
		auto cur = que.front();	
		que.pop();

		if (cur.first == "Enter")			// Queue has only two instructions such as "Enter" and "Leave".
			result = m[cur.second] + "���� ���Խ��ϴ�.";
		else
			result = m[cur.second] + "���� �������ϴ�.";
		
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