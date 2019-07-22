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
		return a.first < b.first;				// [count가 같은 경우, 숫자는 오름차순.]

	return a.second < b.second;			// The count is the main factor to do sort in ascending order.
}

void R_rotate()			// To figure out how many numbers are in each row.
{
	vector<pair<int, int>> vc[MAX];	// vc = The temporary memory of number and count's pair.	
													//  first = number.		second = count.	
	for (int i = 1; i <= row; i++)			// [모든 row(행)을 차례대로.]
	{
		int cnt[MAX] = { 0, };				// cnt = The temporary memory of count.
		for (int j = 1; j <= col; j++)		// [Row에 있는 모든 value를 순서대로 check하면서 coutnt.]
			cnt[arr[i][j]]++;					// [해당 num의 cnt index에 직접 접근해서 count 증가.]	

		for (int j = 1; j < MAX; j++)		// [간과했던 부분.]
			if (cnt[j])							// [array 안에 있는 값이 row, col 보다 큰 수일 수 있기 때문에, 처음부터 끝까지 search해야 한다.]
				vc[i].push_back(make_pair(j, cnt[j]));		// [해당 num과 cnt를 vector에 pair 형태로 저장.]
	}

	for (int i = 1; i <= row; i++)			// [count와 num을 각 각 오름차순으로 정렬.]
	{												// [count is the main factor to do sort.]
		sort(vc[i].begin(), vc[i].end(), comp);
		col = max(col, (int)vc[i].size() * 2);	// [array에는 num과 cnt가 각각 저장되기 때문에, array의 index는 2개씩 저장된다.]
	}														// [이를 기반으로, 가장 큰 column의 size를 구해놓는다.]	

	for (int i = 1; i <= row; i++)			// [row 기준의 rotation이기 때문에, 각 row 마다 update.]
	{
		int k = 1;
		for (int j = 0; j < vc[i].size(); j++)	// vc has sorted value.
		{
			arr[i][k++] = vc[i][j].first;		// The number will be stored first in array.	
			arr[i][k++] = vc[i][j].second;	// The count will be stored second in array.
		}

		for (int j = k; j <= col; j++)				// If there is empty space, it should be stored as zero.
			arr[i][j] = 0;							// [최대 column size만큼, 빈 array에는 0으로 초기화.]	
	}
}

void C_rotate()			// To figure out how many numbers are in each row.
{
	vector<pair<int, int>> vc[MAX];	// vc = The temporary memory of number and count's pair.	
													//  first = number.		second = count.	
	for (int i = 1; i <= col; i++)			// [모든 column(열)을 차례대로.]
	{
		int cnt[MAX] = { 0, };				// cnt = The temporary memory of count.
		for (int j = 1; j <= row; j++)		// [Column에 있는 모든 value를 순서대로 check하면서 coutnt.]
			cnt[arr[j][i]]++;					// [해당 num의 cnt index에 직접 접근해서 count 증가.]	

		for (int j = 1; j < MAX; j++)		// [간과했던 부분.]
			if (cnt[j])							// [array 안에 있는 값이 row, col 보다 큰 수일 수 있기 때문에, 처음부터 끝까지 search해야 한다.]
				vc[i].push_back(make_pair(j, cnt[j]));		// [해당 num과 cnt를 vector에 pair 형태로 저장.]
	}

	for (int i = 1; i <= col; i++)			// [count와 num을 각 각 오름차순으로 정렬.]
	{												// [count is the main factor to do sort.]
		sort(vc[i].begin(), vc[i].end(), comp);
		row = max(row, (int)vc[i].size() * 2);		// [array에는 num과 cnt가 각각 저장되기 때문에, array의 index는 2개씩 저장된다.]
	}															// [이를 기반으로, 가장 큰 column의 size를 구해놓는다.]	

	for (int i = 1; i <= col; i++)			// [column 기준의 rotation이기 때문에, 각 column 마다 update.]
	{
		int k = 1;
		for (int j = 0; j < vc[i].size(); j++)			// vc has sorted value.
		{
			arr[k++][i] = vc[i][j].first;				// The number will be stored first in array.
			arr[k++][i] = vc[i][j].second;			// The count will be stored second in array.
		}

		for (int j = k; j <= row; j++)	// If there is empty space, it should be stored as zero.
			arr[j][i] = 0;					// [최대 row size만큼, 빈 array에는 0으로 초기화.]	
	}
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	memset(arr, -1, sizeof(arr));			// Initiation as -1 to distinguish zero value which was used for empty space.
														// [empty space를 0으로 채우는 것과 구분하기 위해, 초기화는 -1로 한다.]
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