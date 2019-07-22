#pragma warning(disable:4996)
#include <stdio.h>
#include<math.h>
// 5 - 1
/*
int check[10000] = { 0, };
int Sum(int);
int main()
{
	for (int i = 1; i <= 10000; i++)
		Sum(i);

	for (int i = 1; i <= 10000; i++)
	{
		if (check[i] == 0)
			printf("%d \n", i);
	}
}

int Sum(int n)
{
	int temp_1, temp_2, temp_3, temp_4, sum;

	if (n < 100)
	{
		temp_1 = n / 10;
		temp_2 = n % 10;
		sum = n + temp_1 + temp_2;
	}
	else if (n < 1000)
	{
		temp_1 = n / 100;
		temp_2 = (n % 100) / 10;
		temp_3 = n % 10;
		sum = n + temp_1 + temp_2 + temp_3;
	}
	else if (n <= 10000)
	{
		temp_1 = n / 1000;
		temp_2 = (n % 1000) / 100;
		temp_3 = (n % 100) / 10;
		temp_4 = n % 10;
		sum = n + temp_1 + temp_2 + temp_3 + temp_4;
	}
	check[sum]++;

	if (sum > 10000)
		return 0;
	Sum(sum);
}
*/

// 5 - 2
/*
int one_num(int num){
	int i;
	int arr[4] = { 0, };

	for (i = 0; num > 0; i++, num /= 10){ //각자리수를 배열에 하나씩 입력
		arr[i] = num % 10;
	}

	while (i--){
		if (i < 2)return 1; //2자리수 이하는 무조건 한수이기 때문에 return1

		int a = arr[i] - arr[i - 1]; //등차
		int b = arr[i - 1] - arr[i - 2]; //등차
		if (a != b)return 0;
	}
}
int main()
{
	int num, i, count = 0;

	scanf("%d", &num);

	for (i = 1; i <= num; i++){
		if (one_num(i)) //한수면 return 1 아니면 return 0
			count++;
	}
	printf("%d", count);
}
*/

// 5 - 3
/*
int Star(int, int);
int main()
{
	int N, check = 0;
	scanf("%d", &N);

	for (int k = 0; k <= 10; k++)
	{
		if (N == 3 * pow(2,k))
			check = pow(2,k);
	}
	
	if (check != 0)
		Star(N, check);
}

int Star(int num, int k)
{
	for (int i = 1; i <= k; i++)
	{
		printf("*");
	}
}
*/