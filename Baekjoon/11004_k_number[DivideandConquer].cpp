#include<iostream>
#pragma warning(disable:4996)

using namespace std;

int N, K;						// N = The number of whole number set.		K = The k'th number in a set.
int *num;					// Number set.
int *sorted;

void Conquer(int left, int mid, int right)
{
	int i = left, j = mid + 1, idx = left;
	
	while (i<=mid && j<=right)
	{
		if (num[i] < num[j])
		{
			sorted[idx] = num[i];
			i++;	
			idx++;
		}

		else 
		{
			sorted[idx] = num[j];
			j++;	
			idx++;
		}
	}

	while (i <= mid)
	{
		sorted[idx] = num[i];
		i++;	idx++;
	}

	while (j <= right)
	{
		sorted[idx] = num[j];
		j++;	idx++;
	}

	for (int k = left; k <= right; k++)
		num[k] = sorted[k];
}

void Divide(int left, int right)
{
	int mid = (left + right) / 2;						// To split 2 way.
	if(left < right)
	{
		Divide(left, mid);								// Splited left part.
		Divide(mid+1, right);						// Splited right part.
		Conquer(left, mid, right);					// Merge(conquer) each elements.
	}
}

int main(void)
{
	scanf("%d %d",&N,&K);		// Input of the number of num set and k'th order.

	num = new int[N];
	for (int i = 0; i < N; i++)
		scanf("%d",&num[i]);

	sorted = new int[N];
	Divide(0, N-1);
	
	cout << num[K-1] << endl;
}