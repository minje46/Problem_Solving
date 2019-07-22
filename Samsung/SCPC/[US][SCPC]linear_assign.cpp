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

		// 각 정점 V에 연결된 node의 수를 기준으로 내림차순 하여, degree 기준으로 linear 배치 하는 방법 시도. -> 1번 예제 fail. (2번 예제 success.)
		// 동일한 node의 수가 연결되어 있을 때, node의 distance를 계산하여 내림차순 하여 linear 배치하는 방법 시도. -> 1번 예제 success. (2번 예제 fail.)

		//	Answer = 0;
		// Print the answer to standard output(screen).
		cout << "Case #" << test_case + 1 << endl;
		cout << Answer << endl;
	}

	return 0;
}