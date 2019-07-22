#include <iostream>
#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

int N;

void init(vector<int> &arr, vector<int> &tree, int node, int start, int end)			// Initialize the segment tree with index of minimum height.
{
	if (start == end)						// [start==end ��� ����, leaf node��� ���� �ǹ��Ѵ�.]
		tree[node] = start;				// [Node���� value�� �ƴ� array�� index�� �����Ѵ�.]

	else
	{
		int mid = (start + end) / 2;										// [������ ������ ���� Divide.]
		init(arr, tree, node * 2, start, mid);							// Left part.
		init(arr, tree, node * 2 + 1, mid + 1, end);					// Right part.

		if (arr[tree[node * 2]] <= arr[tree[node * 2 + 1]])		// Compare child nodes.
			tree[node] = tree[node * 2];								// [Merge �ϸ鼭, minimum height�� parent node�� ����.]
		else
			tree[node] = tree[node * 2 + 1];
	}
}

int query(vector<int> &arr, vector<int> &tree, int node, int start, int end, int left, int right)		// Get the minimum height's index in array.
{
	if (left > end || right < start)					// [left,right] ������ [start,end] ���� �ۿ� �ִ� ���.
		return -1;										// Return unmeaningful value.
	
	if (left <= start && end <= right)			// [start,end] ������ [left,right] ���� ���ο� �ִ� ���.
		return tree[node];							// Return current node which has index. [���� ������ �ִ� ���� Minimum height's index value.]
	
	int m1 = query(arr, tree, 2 * node, start, (start + end) / 2, left, right);				// [������ �κ������� ��ġ�� ���.]
	int m2 = query(arr, tree, 2 * node + 1, (start + end) / 2 + 1, end, left, right);		// Additional division is needed.
	
	if (m1 == -1)										// Range is wrong.
		return m2;										// Don't care this case.
		
	else if (m2 == -1)								// ������ ���� �ٸ� case.	 
		return m1;										// �ǹ� ���� �� -1�� return ���� ��.
	
	else													// Pick the minimum height's index between values.
	{														// [Return ���� node�� value �߿��� minimum value�� ����.]
		if (arr[m1] <= arr[m2]) 
			return m1;	
		else 
			return m2;
	}
}

long long largest(vector<int> &arr, vector<int> &tree, int start, int end) 
{
	int m = query(arr, tree, 1, 0, N - 1, start, end);								// To get the minimum height's index.

	long long area = (long long)(end - start + 1)*(long long)arr[m];		// Calculate square area.

	if (start <= m - 1)					// Check it has left parts.
	{
		long long temp = largest(arr, tree, start, m - 1);
		if (area < temp)					// Is it maximum area?
			area = temp;
	}

	if (m + 1 <= end)						// Check it has right parts.
	{
		long long temp = largest(arr, tree, m + 1, end);
		if (area < temp)					// Is it maximum area?
			area = temp;
		
	}

	return area;					// Return max area.
}

int main(void)
{
	while (1)
	{
		cin >> N;												// The number of elements.
		if (N == 0)
			break;

		vector<int> arr(N);									// Allocate memory.
		for (int i = 0; i < N; i++)
			cin >> arr[i];										// Input of each elements.
																	
		int h = (int)(ceil(log2(N)));							// To build size of tree, getting a height.
		int tree_size = (1 << (h + 1));					// [Segment tree �� size �� ���Ѵ�.] 

		vector<int> tree(tree_size);						// Allocate memory.
		init(arr, tree, 1, 0, N - 1);							// Initialize the segment tree.	

		cout << largest(arr, tree, 0, N - 1) << endl;
	}
}