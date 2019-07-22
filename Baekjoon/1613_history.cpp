#include<iostream>
#pragma warning(disable:4996)

#define MAX 402

using namespace std;

int history[MAX][MAX];							// The memory of history's events.

void Floyd_warshall(int N)						// To figure out the event's order.
{
	for (int k = 1; k <= N; k++)				// The connection between events.	[삼단논법으로 찾을 수 있는 사건의 관계.]
		for (int i = 1; i <= N; i++)				// The first event.	[먼저 발생한 사건.]
			for (int j = 1; j <= N; j++)			// The second event.	[나중에 발생한 사건.]
				if (i == j || j == k || i == k)	// It's no use to check. [동일한 사건의 전후관계를 파악할 의미가 없다.]
					continue;
				else
				{
					if (history[i][j] == 0)		// The case of what we don't know the order. 
					{									// [Input을 받지 못하여, 파악할 수 없는 사건의 순서를 의미.]
						if (history[i][k] == 1 && history[k][j] == 1)	// [사건 i가 k보다 나중에 발생했고, 
							history[i][j] = 1;					// 사건 k가 j보다 후에 발생하였다면, 사건 i가 j보다 후에 발생한 것.]
						else if (history[i][k] == -1 && history[k][j] == -1)	// [사건 i가 k보다 먼저 발생했고,
							history[i][j] = -1;				// 사건 k가 j보다 먼저 발생하였다면, 사건 i가 j보다 먼저 발생한 것.]
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