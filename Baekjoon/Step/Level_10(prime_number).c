#pragma warning(disable:4996)
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

// 10 - 1
/*
int Prime_Number(int N, int *num)
{
	int count = 0, check = 0;

	for (int i = 0; i < N; i++)
	{
		if (num[i] == 1)
			continue;
		else if (num[i] == 2)
		{
			count++;
			continue;
		}
		for (int j = 2; j < num[i]; j++)
		{
			if (num[i] % j == 0)
			{
				check = 1;
				break;
			}
		}
		if (check)
			check = 0;
		else
			count++;
	}
	return count;
}

int main()
{
	int N, num[100] = { 0, };

	scanf("%d", &N);
	for (int i = 0; i < N; i++)
		scanf("%d", &num[i]);
	
	printf("%d \n", Prime_Number(N, &num));
}
*/

// 10 - 2 (Return 값은 1개만 가능.(일반적의 경우에서는))
/*
int min = -1;
int Prime(int N, int *num)
{
	int check = 0, total = 0;

	for (int i = 0; i < N; i++)
	{
		if (num[i] == 1)
			continue;
		else if (num[i] == 2)
		{
			min = 2;
			total += 2;
			continue;
		}
		for (int j = 2; j < num[i]; j++)
		{
			if (num[i] % j == 0)
			{
				check = 1;
				break;
			}
		}
		if (check)
			check = 0;
		else
		{
			if (total == 0)
				min = num[i];
			total += num[i];
		}
	}
	if (min == -1)
		return -1;
	else
		return total;
}
int main()
{
	int M, N, num[10000] = { 0, };

	scanf("%d", &M);
	scanf("%d", &N);

	for (int i = 0; i < (N - M) + 1; i++)
		num[i] = M + i;

	printf("%d\n",Prime((N - M) + 1, &num));
	if (min != -1)
		printf("%d\n",min);
}
*/

// 10 - 3 (에라토스테네의 체)
/*
#define Size 1000001
int num[Size];
int Eratos()
{
	int j = 2;
	
	for (int i = 1; i < Size; i++)
	{	
		if (i == 1)
			num[i] = -1;

		while ((num[i] * j < Size) && (num[i] != -1))
		{
			num[num[i] * j] = -1;
			j++;
		}
		j = 2;
	}
}	

int main()
{
	int M, N;

	for (int i = 1; i < Size; i++)
		num[i] = i;

	Eratos();

	scanf("%d %d", &M, &N);

	for (int i = M; i < N + 1; i++)
		if (num[i] != -1)
			printf("%d\n", num[i]);
}
*/

// 10 - 4 (베르트랑 공준)
/*
#define Size 300000
int num[Size];
int Bertrand(int N)
{
	int count = 0;
	
	for (int i = N+1; i <= 2 * N; i++)
	{
		if (num[i] != -1)
			count++;
	}
	return count;
}

int Eratos()
{
	int j = 2;

	for (int i = 1; i < Size; i++)
	{
		if (i == 1)
			num[i] = -1;

		while ((num[i] * j < Size) && (num[i] != -1))
		{
			num[num[i] * j] = -1;
			j++;
		}
		j = 2;
	}
}

int main()
{
	int N;
	
	for (int i = 1; i < Size; i++)
		num[i] = i;

	Eratos();

	while (1)
	{
		scanf("%d", &N);
		if (N == 0)
			break;

		printf("%d\n", Bertrand(N));
	}
}
*/

// 10 - 5 (골드바흐의 추측)
/*
#define Size 10001
int num[Size];
int Goldbach(int N)
{
	int a, b, min = 10000, i = N / 2, j = N / 2;
	
	while (i >= 2 && j < N)
	{
		if (num[i] != -1 && num[j] != -1)
		{
			if ((N == i + j) && ((j - i) < min) && ((j - i) >= 0))
			{
				a = i;
				b = j;
				min = b - a;
				if (min == 0)
					break;
			}
		}
		j++;
		i--;
	}
	printf("%d %d \n", a, b);
}

int Eratos()
{
	int j = 2;

	for (int i = 1; i < Size; i++)
	{
		if (i == 1)
			num[i] = -1;

		while ((num[i] * j < Size) && (num[i] != -1))
		{
			num[num[i] * j] = -1;
			j++;
		}
		j = 2;
	}
}

int main()
{
	int T, N;

	for (int i = 1; i < Size; i++)
		num[i] = i;

	Eratos();
	
	scanf("%d", &T);
	for (int i = 0; i < T; i++)
	{
		scanf("%d", &N);
		Goldbach(N);
	}
}
*/