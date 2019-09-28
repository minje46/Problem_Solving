#include<stdio.h>
#pragma warning(disable:4996)

int main(void)
{
	int N, K, idx = 0;				// N = The number of value's digit.		K = Number to delete.			idx = The index of array as top in stack.
	char ch, stk[500000];		// ch = The temporary memory to get character each by each.			stk = The array to store values as stack.

	scanf("%d %d", &N, &K);
	while (N--)
	{
		do											// If others are scanned, it should get again.
			scanf("%c", &ch);				// [0~9 외의 character는 while을 통해 다시 입력.]
		while (ch < 48 || 57 < ch);		// The condition for getting number only.

		while (K > 0 && idx > 0 && stk[idx - 1] < ch)		// Conditions for making bigger values.
		{
			idx--;		// Reorganize index.
			K--;			// It means the small number was deleted.
		}

		stk[idx++] = ch;		// Except that condition, the value should be stored in stack.
	}

	idx -= K;		// If the values to delete exists, it should be handeled with.
	stk[idx] = 0;	// Make it finish one string.
	puts(stk);		// And use puts.
}