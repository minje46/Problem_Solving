#pragma warning(disable:4996)
#include<iostream>
#include<algorithm>
#include<vector>

#define MAX 101

using namespace std;

int Answer;
vector<int, int> graph[MAX];
vector<int> list;

int main(int argc, char** argv)
{
	int T, test_case;

	freopen("input.txt", "r", stdin);

	cin >> T;
	for (test_case = 0; test_case < T; test_case++)
	{
		int V, E;
		cin >> V >> E;
		for (int i = 0; i < E; i++)
		{
			int u, v;
			cin >> u >> v;
			graph[u].push_back(make_pair(u, v));
	
		}

//		List();

//		Answer = Count();

		// �� ���� V�� ����� node�� ���� �������� �������� �Ͽ�, degree �������� linear ��ġ �ϴ� ��� �õ�. -> 1�� ���� fail. (2�� ���� success.)
		// ������ node�� ���� ����Ǿ� ���� ��, node�� distance�� ����Ͽ� �������� �Ͽ� linear ��ġ�ϴ� ��� �õ�. -> 1�� ���� success. (2�� ���� fail.)

		//	Answer = 0;
		// Print the answer to standard output(screen).
		cout << "Case #" << test_case + 1 << endl;
		cout << Answer << endl;
	}

	return 0;
}