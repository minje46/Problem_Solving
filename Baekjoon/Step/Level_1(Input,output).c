#pragma warning(disable:4996)
# include <stdio.h>
/*
// 1-1
int main()
{
	printf("Hello world!");
	
	return 0;
}
*/

// 1-2
/*
int main()
{
	//int A, B;
	double A, B;

	scanf("%lf %lf", &A, &B);
	//printf("%d", A + B);
	//printf("%d", A - B);
	//printf("%d", A*B);
	printf("%.9lf", A/B);
}
*/
// 1-2(2)
/*
int main()
{
	int N, big, small, total = 0;// N �� �ѹ��� , big �� 5kg¥�� ���� , small �� 3kg ¥�� ���� , total �� �Ѱ���
	scanf("%d", &N);

	if (N >= 3 && N <= 5000)
	{
		for (big = 0; big <= (N/3); big++)
			for (small = 0; small <= (N / 3); small++)
			{
				if (N == 5 * big + 3 * small)
				{
					total = big + small;
				}
			}

		if (total == 0)
			printf("-1\n");
		else
			printf("%d\n", total);
	}
	return 0;
}
*/
// 1-3
/*
int main()
{
	printf("����ģ�� ��������\n");
	printf("����ģ�� ��������\n");
}
*/

// 1-4
/*
int main()
{
	char *a, *b, *c;
	
	a = (char*)malloc(100);
	b = (char*)malloc(100);
	c = (char*)malloc(100);

	gets(a); gets(b);gets(c);
	puts(a);puts(b);puts(c);
	free(a); free(b); free(c);
}
*/

