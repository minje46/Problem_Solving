#pragma warning(disable:4996)
# include <stdio.h>

// 3 - 1
/*
int main()
{
	int N;

	scanf("%d", &N);

	for (int i = 1; i <= N; i++)
		printf("%d \n", i);

}
*/

// 3 - 3
/*
int main()
{
	int N;

	scanf("%d", &N);

	for (int i = 1; i <= 9; i++)
		printf("%d * %d = %d \n", N, i, N*i);
}
*/

// 3 - 4
/*
int main()
{
	int N;

	scanf("%d", &N);

	for (int i = 1; i <= N; i++)
	{
		for (int j = N; j > i; j--)
			printf(" ");
		for (int k = 1; k <= i; k++)
			printf("*");
		printf("\n");
	}
}
*/

// 3 - 5
/*
int main()
{
	int N;
	scanf("%d", &N);

	for (int i = 0; i < N; i++)
	{
		for (int j = N; j > i; j--)
			printf("*");
		printf("\n");
	}
}
*/

// 3 - 5(2)
/*
int main()
{
	int N;
	scanf("%d", &N);

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < i; j++)
			printf(" ");
		for (int k = N; k > i; k--)
			printf("*");
		printf("\n");
	}
}
*/

// 3 - 6
/*
int main()
{
	int x, y, total=0, day;
	
	scanf("%d %d", &x, &y);
	if ((x >= 1) && (x <= 12))
	{
		if ((y >= 1) && (y <= 31))
		{
			for (int i = 1; i < x; i++)
			{
				if ((i == 1) || (i == 3) || (i == 5) || (i == 7) || (i == 8) || (i == 10) || (i == 12))
					total = total +  31;
				else if (i == 2)
					total = total + 28;
				else
					total = total +  30;
			}
		}
	}

	total = total + y ;
	day = total % 7;

	if (day == 0)
		printf("SUN \n");
	if (day == 1)
		printf("MON \n");
	if (day == 2)
		printf("TUE \n");
	if (day == 3)
		printf("WED \n");
	if (day == 4)
		printf("THU \n");
	if (day == 5)
		printf("FRI \n");
	if (day == 6)
		printf("SAT \n");
}
*/

// 3 - 10
/*
int main()
{
	int N, sum = 0;
	char x[50], buf;

	scanf("%d", &N);
	scanf("%c", &buf); // 정수 입력받고 \n 씹히는것.
	scanf("%s", &x);

	for (int i = 0; i < N; i++)
		sum = sum + (x[i] - '0');

	printf("%d\n", sum);
}
*/

// 3 - 11
/*
#include<string.h>
int main()
{
	int j = 0;
	char str[200], out[200];

	scanf("%s", str);
	for (int i = 0; i < strlen(str); i++)
	{
		out[j] = str[i];
		if ((i + 1) % 10 == 0)
			out[++j] = '\n';
		j++;
	}
	out[j] = '\0';
	printf("%s", out);
}
*/
