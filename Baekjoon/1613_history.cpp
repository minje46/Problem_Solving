#include<iostream>
#pragma warning(disable:4996)

#define MAX 402

using namespace std;

int history[MAX][MAX];							// The memory of history's events.

void Floyd_warshall(int N)						// To figure out the event's order.
{
	for (int k = 1; k <= N; k++)				// The connection between events.	[��ܳ������ ã�� �� �ִ� ����� ����.]
		for (int i = 1; i <= N; i++)				// The first event.	[���� �߻��� ���.]
			for (int j = 1; j <= N; j++)			// The second event.	[���߿� �߻��� ���.]
				if (i == j || j == k || i == k)	// It's no use to check. [������ ����� ���İ��踦 �ľ��� �ǹ̰� ����.]
					continue;
				else
				{
					if (history[i][j] == 0)		// The case of what we don't know the order. 
					{									// [Input�� ���� ���Ͽ�, �ľ��� �� ���� ����� ������ �ǹ�.]
						if (history[i][k] == 1 && history[k][j] == 1)	// [��� i�� k���� ���߿� �߻��߰�, 
							history[i][j] = 1;					// ��� k�� j���� �Ŀ� �߻��Ͽ��ٸ�, ��� i�� j���� �Ŀ� �߻��� ��.]
						else if (history[i][k] == -1 && history[k][j] == -1)	// [��� i�� k���� ���� �߻��߰�,
							history[i][j] = -1;				// ��� k�� j���� ���� �߻��Ͽ��ٸ�, ��� i�� j���� ���� �߻��� ��.]
					}
				}
}


int main(void)
{
	int N, M, Q;
	scanf("%d %d", &N, &M);		// N = The number of events.		M = The number of data.
	for (int i = 0; i < M; i++)			// Input of the event's order.
	{
		int a, b;
		scanf("%d %d", &a, &b);
		history[a][b] = -1;					// It was happened before.
		history[b][a] = 1;					// It was happened later.	
	}

	Floyd_warshall(N);					// To figure out the event's order.

	scanf("%d", &Q);
	for (int i = 0; i < Q; i++)
	{
		int a, b;
		scanf("%d %d", &a, &b);

		printf("%d \n", history[a][b]);		// The output of the event's order.
	}
}