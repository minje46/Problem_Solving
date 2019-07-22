#pragma warning(disable:4996)
# include <stdio.h>

// 4 - 2
/*
int main()
{
	int num[10], total = 0, max, min;
	scanf("%d %d %d", &num[0], &num[1], &num[2]);

	for (int i = 0; i < 3; i++)
	{
		total = total + num[i];
		if (i == 0)
		{
			max = num[0];
			min = num[0];
		}
		if (num[i] >= max)
			max = num[i];
		if (num[i] <= min)
			min = num[i];
	}
	printf("%d \n", total - max - min);
}
*/

// 4 - 3 
/*
int main()
{
	int num[50] = { 0, }, N, X, min[20], j = 0;
	scanf("%d %d", &N, &X);

	for (int i = 0; i < N; i++)
		scanf("%d", &num[i]);
	
	for (int i = 0; i < N; i++)
	{
		if (num[i] < X)
			min[j++] = num[i];
	}

	for (int i = 0; i < j; i++)
		printf("%d ",min[i]);
	printf("\n");
}
*/

// 4 - 4
/*
int main()
{
	int N, max;
	float sub[1000] = { 0, }, total = 0;
	scanf("%d", &N);

	for (int i = 0; i < N; i++)
		scanf("%f", &sub[i]);
	
	for (int i = 0; i < N; i++)
	{
		if (i == 0)
			max = sub[i];

		if (max < sub[i])
			max = sub[i];
	}

	for (int i = 0; i < N; i++)
	{
		sub[i] = sub[i] / max * 100;
		total = total + sub[i];
	}
	printf("%.2f\n", total / N);
}
*/

// 4 - 5
/*
int main()
{
	int C, N, count = 0;
	float score[1000] = { 0, }, total = 0, avg;
	scanf("%d", &C);

	for (int i = 0; i < C; i++)
	{
		scanf("%d", &N);
		for (int j = 0; j < N; j++)
		{
			scanf("%f", &score[j]);
			total = total + score[j];
		}
		avg = total / N;
		for (int j = 0; j < N; j++)
		{
			if (score[j] > avg)
				count++;
		}
		printf("%.3f%%\n", (float)count / N * 100);
		count = 0;
		total = 0;
	}
}
*/

// 4 - 6
/*
int main()
{
	int N, len = 0, temp_1, temp_2, sum, changed;
	scanf("%d", &N);
	changed = N;
	while (1)
	{
		temp_1 = changed / 10;
		temp_2 = changed % 10;
		sum = temp_1 + temp_2;
		changed = (temp_2 * 10) + (sum % 10);
		len++;
		
		if (N == changed)
			break;
	}
	printf("%d\n", len);
}
*/