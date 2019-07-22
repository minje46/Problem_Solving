#include<iostream>
#include<algorithm>
#include<vector>

#define MAX 100001

using namespace std;

int N, cnt;					// N = The number of students.			cnt = The total counts of team members.
vector<int>student;		// The memory of all students and team mates who they wanna be together.
bool visit[MAX];			// The memory of whether visited or not.
bool check[MAX];		// The additional memory to check cycle exists or not. 
								// [check는 visit 했지만, 아직 dfs가 진행 중인 cycle을 이루는 node를 확인하기 위한 부가적 메모리다.]	
void DFS(int node)		// To figure out there is successful team or not.
{
	visit[node] = true;	// [현재 node 방문 했다는 것.]

	int next = student[node];	
	if (!visit[next])			// [다음 node로 연결되어 있는 것 중, 방문하지 않은 node는 dfs.]
		DFS(next);

	else if (!check[next])	// [다음 node가 visit=true 라는 것은, cycle을 이룬다는 의미이다.]
	{								// [추후의 중복되는 cycle 여부 확인을 방지하기 위한 additional check memory를 사용.]
		for (int start = next; start != node; start = student[start])	// [Backtracking 방식을 통해, start node에서 end node까지 차례대로 방문.]
			cnt++;				// [Team을 이루는 node의 수 count.]// [start node와 end node는 같은 값이다. 그래야 cycle이 형성되니까..]
		cnt++;					// [첫 번째, start=end node의 수를 count.]
	}

	check[node] = true;	// [Cycle의 여부를 확인 했기에, 추후 중복 search를 방지할 수 있다.]
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	int T;		// T = The number of test case.	
	cin >> T;
	while (T--)
	{
		// Initialization.
		student.clear();
		fill(check, check+MAX, false);
		fill(visit, visit + MAX, false);

		cin >> N;
		for (int i = 0; i <= N; i++)
		{
			if (i == 0)							// [N을 1부터 시작하기 위한 방법.]
			{										// [Vector를 이용하여, 동적 메모리 할당을 하기 위함.]	
				student.push_back(0);		// [정적으로 할당하면 불필요한 짓.]
				continue;
			}
			int member;
			cin >> member;
			student.push_back(member);	// Organize input data.
		}

		cnt = 0;
		for (int i = 1; i <= N; i++)		
			if (!visit[i])		// Check only not visited node.
				DFS(i);		// To figure out there is successful team or not.
								// Also it counts the successful team members as well.	
		cout << N-cnt << endl;				// Output.
	}
}