#include<iostream>
#include<algorithm>
#include<vector>
#include<memory.h>

#define MAX 101

using namespace std;

int arr[MAX][MAX];		// arr = The memory of array.
int row = 3, col = 3;		// row = The memory of rows.		col = The memory of columns.

bool comp(const pair<int, int>&a, const pair<int, int>&b)		// To do custom sorting.
{
	if (a.second == b.second)			// If the count is same, the number sorts in ascending order.	
		return a.first < b.first;				// [count�� ���� ���, ���ڴ� ��������.]

	return a.second < b.second;			// The count is the main factor to do sort in ascending order.
}

void R_rotate()			// To figure out how many numbers are in each row.
{
	vector<pair<int, int>> vc[MAX];	// vc = The temporary memory of number and count's pair.	
													//  first = number.		second = count.	
	for (int i = 1; i <= row; i++)			// [��� row(��)�� ���ʴ��.]
	{
		int cnt[MAX] = { 0, };				// cnt = The temporary memory of count.
		for (int j = 1; j <= col; j++)		// [Row�� �ִ� ��� value�� ������� check�ϸ鼭 coutnt.]
			cnt[arr[i][j]]++;					// [�ش� num�� cnt index�� ���� �����ؼ� count ����.]	

		for (int j = 1; j < MAX; j++)		// [�����ߴ� �κ�.]
			if (cnt[j])							// [array �ȿ� �ִ� ���� row, col ���� ū ���� �� �ֱ� ������, ó������ ������ search�ؾ� �Ѵ�.]
				vc[i].push_back(make_pair(j, cnt[j]));		// [�ش� num�� cnt�� vector�� pair ���·� ����.]
	}

	for (int i = 1; i <= row; i++)			// [count�� num�� �� �� ������������ ����.]
	{												// [count is the main factor to do sort.]
		sort(vc[i].begin(), vc[i].end(), comp);
		col = max(col, (int)vc[i].size() * 2);	// [array���� num�� cnt�� ���� ����Ǳ� ������, array�� index�� 2���� ����ȴ�.]
	}														// [�̸� �������, ���� ū column�� size�� ���س��´�.]	

	for (int i = 1; i <= row; i++)			// [row ������ rotation�̱� ������, �� row ���� update.]
	{
		int k = 1;
		for (int j = 0; j < vc[i].size(); j++)	// vc has sorted value.
		{
			arr[i][k++] = vc[i][j].first;		// The number will be stored first in array.	
			arr[i][k++] = vc[i][j].second;	// The count will be stored second in array.
		}

		for (int j = k; j <= col; j++)				// If there is empty space, it should be stored as zero.
			arr[i][j] = 0;							// [�ִ� column size��ŭ, �� array���� 0���� �ʱ�ȭ.]	
	}
}

void C_rotate()			// To figure out how many numbers are in each row.
{
	vector<pair<int, int>> vc[MAX];	// vc = The temporary memory of number and count's pair.	
													//  first = number.		second = count.	
	for (int i = 1; i <= col; i++)			// [��� column(��)�� ���ʴ��.]
	{
		int cnt[MAX] = { 0, };				// cnt = The temporary memory of count.
		for (int j = 1; j <= row; j++)		// [Column�� �ִ� ��� value�� ������� check�ϸ鼭 coutnt.]
			cnt[arr[j][i]]++;					// [�ش� num�� cnt index�� ���� �����ؼ� count ����.]	

		for (int j = 1; j < MAX; j++)		// [�����ߴ� �κ�.]
			if (cnt[j])							// [array �ȿ� �ִ� ���� row, col ���� ū ���� �� �ֱ� ������, ó������ ������ search�ؾ� �Ѵ�.]
				vc[i].push_back(make_pair(j, cnt[j]));		// [�ش� num�� cnt�� vector�� pair ���·� ����.]
	}

	for (int i = 1; i <= col; i++)			// [count�� num�� �� �� ������������ ����.]
	{												// [count is the main factor to do sort.]
		sort(vc[i].begin(), vc[i].end(), comp);
		row = max(row, (int)vc[i].size() * 2);		// [array���� num�� cnt�� ���� ����Ǳ� ������, array�� index�� 2���� ����ȴ�.]
	}															// [�̸� �������, ���� ū column�� size�� ���س��´�.]	

	for (int i = 1; i <= col; i++)			// [column ������ rotation�̱� ������, �� column ���� update.]
	{
		int k = 1;
		for (int j = 0; j < vc[i].size(); j++)			// vc has sorted value.
		{
			arr[k++][i] = vc[i][j].first;				// The number will be stored first in array.
			arr[k++][i] = vc[i][j].second;			// The count will be stored second in array.
		}

		for (int j = k; j <= row; j++)	// If there is empty space, it should be stored as zero.
			arr[j][i] = 0;					// [�ִ� row size��ŭ, �� array���� 0���� �ʱ�ȭ.]	
	}
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	memset(arr, -1, sizeof(arr));			// Initiation as -1 to distinguish zero value which was used for empty space.
														// [empty space�� 0���� ä��� �Ͱ� �����ϱ� ����, �ʱ�ȭ�� -1�� �Ѵ�.]
	int r, c, k;										// r = The row index.		c = The column index.			k = The value of array. 		
	cin >> r >> c >> k;	

	for (int i = 1; i <= 3; i++)
		for (int j = 1; j <= 3; j++)
			cin >> arr[i][j];			// Organize the array.

	int answer = 0;					// answer = How many times is the rotation wored. 
	do
	{
		if (arr[r][c] == k)			//	The base case.
			break;

		answer++;

		if (row >= col)					// To do R rotation.
			R_rotate();
		else								// To do C rotation.
			C_rotate();

	} while (answer <= 100);		// Less than 100 times.	
											// Output.
	if (answer > 100)
		cout << -1 << endl;
	else
		cout << answer << endl;
}