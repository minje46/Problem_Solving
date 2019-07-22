#pragma warning(disable:4996)
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

// 6 - 1
/*
int main()
{
	char str[1000000];
	int count = 0;

	fgets(str, sizeof(str),stdin);

	for (int i = 0; i < strlen(str); i++)
	{
		if (((str[i] >= 65) && (str[i] <= 90)) || ((str[i] >= 97) && (str[i] <= 122)))
		{
			if (i == 0)
				count++;
		}
		if ((str[i] == ' ') && (str[i+1] != strlen(str)) && (str[i + 1] != '\n')) 
			{
				if (((str[i + 1] >= 65) && (str[i + 1] <= 90)) || ((str[i + 1] >= 97) && (str[i + 1] <= 122)))
					count++;
			}
	}
	printf("%d\n", count);
}
*/

// 6 - 2
/*
int main()
{
	int A, B, C, mul, check[10] = { 0, };
	char res[100];
	scanf("%d", &A);
	scanf("%d", &B);
	scanf("%d", &C);

	mul = A * B * C;
//	itoa(mul, res, 10);
	sprintf(res, "%d", mul);

	for (int i = 0; i < strlen(res); i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (res[i] - '0' == j)
				check[j]++;
		}
	}
	for (int i = 0; i < 10; i++)
		printf("%d \n", check[i]);
}
*/

// 6 - 3
/*
int main()
{
	int N, score = 0, dup = 0;
	char res[100];
	scanf("%d", &N);
	fflush(stdin);

	for (int i = 0; i < N; i++)
	{
		fgets(res, sizeof(res), stdin);
		for (int j = 0; j < strlen(res); j++)
		{
			if (res[j] == 'O')
			{
				if (dup != 0)
					score = score + dup;
				score++;
				dup++;
			}
			else
				dup = 0;
		}
		printf("%d \n", score);
		score = 0;
		dup = 0;
	}
}
*/

// 6 - 4
/*
int Compare(int*);
int main()
{
	int input[10] = { 0, }, result;

	for (int i = 1; i <= 8; i++)
		scanf("%d", &input[i]);
	
	result = Compare(&input);
	
	if (result == 8)
		printf("ascending \n");
	else if (result == -8)
		printf("descending \n");
	else
		printf("mixed \n");
}

int Compare(int *scale)
{
	int check[10] = { 0, }, count = 0, i = 8;

	for (int j = 1; j <= 8; j++)
	{
		if (scale[j] == j)
			check[j] = 1;	
	}

	for (int j = 1; j <= 8; j++)
	{
		if (scale[j] == i)
			check[j] = -1;	
		i--;
	}
	for (int j = 1; j <= 8; j++)
	{
		if (check[j] == 1)
			count++;
		else if (check[j] == -1)
			count--;
	}
	return count;
}
*/

// 6 - 5
/*
int Calculate(int *, int);
int main()
{
	int score[10];
	
	for (int i = 0; i < 5; i++)
		scanf("%d", &score[i]);
	Calculate(&score, 5);
	return 0;
}

int Calculate(int *sc, int num)
{
	int tot = 0;

	for (int j = 0; j < 5; j++)
	{
		if (sc[j] < 40)
			sc[j] = 40;

		tot += sc[j];
	}
	printf("%d \n", tot / num);
}
*/