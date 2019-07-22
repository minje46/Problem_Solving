#include<iostream>
#include<algorithm>
#include<vector>

#define MAX 100001

using namespace std;

int N, cnt;					// N = The number of students.			cnt = The total counts of team members.
vector<int>student;		// The memory of all students and team mates who they wanna be together.
bool visit[MAX];			// The memory of whether visited or not.
bool check[MAX];		// The additional memory to check cycle exists or not. 
								// [check�� visit ������, ���� dfs�� ���� ���� cycle�� �̷�� node�� Ȯ���ϱ� ���� �ΰ��� �޸𸮴�.]	
void DFS(int node)		// To figure out there is successful team or not.
{
	visit[node] = true;	// [���� node �湮 �ߴٴ� ��.]

	int next = student[node];	
	if (!visit[next])			// [���� node�� ����Ǿ� �ִ� �� ��, �湮���� ���� node�� dfs.]
		DFS(next);

	else if (!check[next])	// [���� node�� visit=true ��� ����, cycle�� �̷�ٴ� �ǹ��̴�.]
	{								// [������ �ߺ��Ǵ� cycle ���� Ȯ���� �����ϱ� ���� additional check memory�� ���.]
		for (int start = next; start != node; start = student[start])	// [Backtracking ����� ����, start node���� end node���� ���ʴ�� �湮.]
			cnt++;				// [Team�� �̷�� node�� �� count.]// [start node�� end node�� ���� ���̴�. �׷��� cycle�� �����Ǵϱ�..]
		cnt++;					// [ù ��°, start=end node�� ���� count.]
	}

	check[node] = true;	// [Cycle�� ���θ� Ȯ�� �߱⿡, ���� �ߺ� search�� ������ �� �ִ�.]
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
			if (i == 0)							// [N�� 1���� �����ϱ� ���� ���.]
			{										// [Vector�� �̿��Ͽ�, ���� �޸� �Ҵ��� �ϱ� ����.]	
				student.push_back(0);		// [�������� �Ҵ��ϸ� ���ʿ��� ��.]
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