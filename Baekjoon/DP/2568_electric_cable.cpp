#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <stack>
#pragma warning(disable:4996)

using namespace std;

int N;												// N = The number of cables.
vector<pair<int, int>> arr;					// arr = Where the cables are connected. (start, end) cable's position.
pair<int, int> trace[100003];			// trace = Memory of tracing the index.
int lis[100003];								// lis = Memory of long increase subset.
bool visit[500003];							//	visti = Check whether cable should be deleted or not.
stack<int> stk;								// stk = Temporary memory to figure out trace's true and false.


int lower_bound(int start, int end, int target)		// Figuring out the position where target value is proper location.
{
	int mid;

	while (start < end)										// Set area.
	{
		mid = (start + end) / 2;

		if (lis[mid] < target)								// [targe value�� ��ġ�� ã�� ���� ���� ��� �̿�.]
			start = mid + 1;									// [Update the start position behind mid.]
		else
			end = mid;
	}
	return end + 1;
}

void LIS()
{
	int idx_lis = 0, idx_arr = 1;								// idx_lis = index of lis memory.		idx_arr = index of input(cable) array.

	lis[idx_lis] = arr[0].second;							// [lis�� �����ϱ� ���� value�� �����Ѵ�.]	[arr�� (index, value)�� ����Ǿ� �ִ�.]
	trace[0].first = 0;										// [trace�� (lis_index, cable_index)�� ����.]
	trace[0].second = arr[0].first;

	while (idx_arr < N)										// 	[Connected cables�� ��ü �Ⱦ�� �ϱ� ������ N���� �ݺ�.]
	{
		if (lis[idx_lis] < arr[idx_arr].second)			// [lis�� ������ ���� ���� arr�� value�� ���ؼ�, value�� �� Ŭ ���, lis�� ���� index�� �������� ����.]
		{
			lis[++idx_lis] = arr[idx_arr].second;		// [value�� ������ ���̱� ������ lis�� ���� index�� ū ���� value�� �����Ѵ�.]

			trace[idx_arr].first = idx_lis;					// [trace�� lis�� index�� cable�� index�� �����Ѵ�.]
			trace[idx_arr].second = arr[idx_arr].first;
		}
		else														// [lis�� ������ ���� ������ arr�� value�� �������.]
		{
			int ans = lower_bound(0, idx_lis, arr[idx_arr].second);		// To figure out index where the new small value is proper. 
			lis[ans - 1] = arr[idx_arr].second;		// [lis�� ���Ӱ� update�� index�� value�� ����.]

			trace[idx_arr].first = ans - 1;				// [trace�� lis�� index�� cable�� index�� �����Ѵ�.]
			trace[idx_arr].second = arr[idx_arr].first;
		}

		idx_arr++;
	}

	printf("%d\n", N - (idx_lis + 1));					// Output of the number of deleted cables. 
														// [��ü N���� cable���� lis+1�� �� ���� deleted cables�� ��.]
	int idx_trace = idx_lis;									// Temporary variable to compare lis's index for a while.

	for (int i = N - 1; i >= 0; i--)							// To trace the index in lis.
		if (trace[i].first == idx_trace)						// [trace�� index�� lis�� index�� ���� ���.]
		{															// [���ǿ� ����.]
			stk.push(trace[i].second);					// [Trace memory���� �ش�Ǵ� ���� extract.]
			idx_trace--;
		}

	while (!stk.empty())
	{
		visit[stk.top()] = false;								// [Stack�� ���� index�� false�� �������ش�.]
		stk.pop();
	}
}

int main(void)
{
	scanf("%d", &N);									// Input the number of electric cables.
	for (int i = 0; i < N; i++)
	{
		int idx, val;											// temproray variables to store index and value.
		scanf("%d %d", &idx, &val);					// Input which cable is connected.

		arr.push_back({ idx, val });					// The data of cable connection is stored in vector.
		visit[idx] = true;									// [Cable�� ����� index�� true�� ����. true�� ���, ���߿� �����ؾ� �ϴ� cable�� �Ǵ� ��.]
	}

	sort(arr.begin(), arr.end());						// Sort by index.

	LIS();														//	Do LIS algorithm.

	for (int i = 0; i <= 500000; i++)
		if (visit[i])											// If it has true value, it should be deleted.
			printf("%d\n", i);							// Output of cable index.	
}