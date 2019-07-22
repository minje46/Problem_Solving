#pragma warning(disable:4996)
#include <stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>

// 9 - 1 (Bubble_Sort) <- Array 로 구현
/*
int Bubble_Sort(int, int *);
int main()
{
	int N, arr[1000];

	scanf("%d", &N);
	for (int i = 0; i < N; i++)
		scanf("%d", &arr[i]);
	
	Bubble_Sort(N, &arr);
	
	for (int i = 0; i < N; i++)
		printf("%d\n", arr[i]);
}

int Bubble_Sort(int N, int *arr)
{
	int temp;

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N - 1; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				temp = arr[j];
				arr[j] = arr[j+1];
				arr[j + 1] = temp;
			}
		}
	}
}
*/

// 9 - 2 (Merge_Sort) <- Array 로 구현
/*
#define Size 1000001
int sort[Size], arr[Size];
int Merge_Sort(int left, int mid, int right)
{
	int i = left, j = mid + 1, n = left;

	while (i <= mid && j <= right)
	{
		if (arr[i] < arr[j])
		{
			sort[n] = arr[i];
			n++;
			i++;
		}
		else
		{
			sort[n] = arr[j];
			n++;
			j++;
		}
	}

	while (i <= mid)
	{
			sort[n] = arr[i];
			n++;
			i++;
	}

	while ( j <= right)
	{
		sort[n] = arr[j];
		n++;
		j++;
	}

	for (int k = left; k <= right; k++)
		arr[k] = sort[k];
}
int Split(int left, int right)
{
	int mid;

	if (left < right)
	{
		mid = (left + right) / 2;
		Split(left, mid);
		Split(mid + 1, right);
		Merge_Sort(left, mid, right);
	}
}
int main()
{
	int N;

	scanf("%d", &N);
	for (int i = 0; i < N; i++)
		scanf("%d", &arr[i]);

	Split(0, N - 1);

	for (int i = 0; i < N; i++)
		printf("%d \n", sort[i]);
}
*/

// Array 참조 시, 의문점.
// *arr
/*
#define Size 101
int sort[Size];
int Merge_Sort(int left, int mid, int right, int *arr)
{
int i = left, j = mid + 1, n = left;

while (i <= mid && j <= right)
{
if (arr[i] < arr[j])
{
sort[n] = arr[i];
n++;
i++;
}
else
{
sort[n] = arr[j];
n++;
j++;
}
}

while (i <= mid)
{
sort[n] = arr[i];
n++;
i++;
}

while (j <= right)
{
sort[n] = arr[j];
n++;
j++;
}

for (int k = left; k <= right; k++)
arr[k] = sort[k];
}
int Split(int left, int right, int *arr)
{
int mid;

if (left < right)
{
mid = (left + right) / 2;
Split(left, mid, &arr);
Split(mid + 1, right, &arr);
Merge_Sort(left, mid, right, &arr);
}
}
int main()
{
int N, arr[Size];

scanf("%d", &N);
for (int i = 0; i < N; i++)
scanf("%d", &arr[i]);

Split(0, N - 1, &arr);

for (int i = 0; i < N; i++)
printf("%d \n", sort[i]);
}
*/

// arr[]
/*
#define Size 101
int sort[Size];
int Merge_Sort(int left, int mid, int right, int arr[])
{
int i = left, j = mid + 1, n = left;

while (i <= mid && j <= right)
{
if (arr[i] < arr[j])
{
sort[n] = arr[i];
n++;
i++;
}
else
{
sort[n] = arr[j];
n++;
j++;
}
}

while (i <= mid)
{
sort[n] = arr[i];
n++;
i++;
}

while (j <= right)
{
sort[n] = arr[j];
n++;
j++;
}

for (int k = left; k <= right; k++)
arr[k] = sort[k];
}
int Split(int left, int right, int arr[])
{
int mid;

if (left < right)
{
mid = (left + right) / 2;
Split(left, mid, arr);
Split(mid + 1, right, arr);
Merge_Sort(left, mid, right, arr);
}
}
int main()
{
int N, arr[Size];

scanf("%d", &N);
for (int i = 0; i < N; i++)
scanf("%d", &arr[i]);

Split(0, N - 1, arr);

for (int i = 0; i < N; i++)
printf("%d \n", sort[i]);
}
*/