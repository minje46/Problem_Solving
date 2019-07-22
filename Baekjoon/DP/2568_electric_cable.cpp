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

		if (lis[mid] < target)								// [targe value의 위치를 찾기 위한 분할 방법 이용.]
			start = mid + 1;									// [Update the start position behind mid.]
		else
			end = mid;
	}
	return end + 1;
}

void LIS()
{
	int idx_lis = 0, idx_arr = 1;								// idx_lis = index of lis memory.		idx_arr = index of input(cable) array.

	lis[idx_lis] = arr[0].second;							// [lis에 저장하기 위한 value를 저장한다.]	[arr에 (index, value)로 저장되어 있다.]
	trace[0].first = 0;										// [trace는 (lis_index, cable_index)로 저장.]
	trace[0].second = arr[0].first;

	while (idx_arr < N)										// 	[Connected cables를 전체 훑어야 하기 때문에 N까지 반복.]
	{
		if (lis[idx_lis] < arr[idx_arr].second)			// [lis의 마지막 저장 값과 arr의 value와 비교해서, value가 더 클 경우, lis의 다음 index에 증가값을 저장.]
		{
			lis[++idx_lis] = arr[idx_arr].second;		// [value가 증가한 값이기 때문에 lis의 다음 index에 큰 값의 value를 저장한다.]

			trace[idx_arr].first = idx_lis;					// [trace에 lis의 index와 cable의 index를 저장한다.]
			trace[idx_arr].second = arr[idx_arr].first;
		}
		else														// [lis의 마지막 저장 값보다 arr의 value가 작은경우.]
		{
			int ans = lower_bound(0, idx_lis, arr[idx_arr].second);		// To figure out index where the new small value is proper. 
			lis[ans - 1] = arr[idx_arr].second;		// [lis에 새롭게 update할 index에 value를 저장.]

			trace[idx_arr].first = ans - 1;				// [trace에 lis의 index와 cable의 index를 저장한다.]
			trace[idx_arr].second = arr[idx_arr].first;
		}

		idx_arr++;
	}

	printf("%d\n", N - (idx_lis + 1));					// Output of the number of deleted cables. 
														// [전체 N개의 cable에서 lis+1을 뺀 값이 deleted cables의 수.]
	int idx_trace = idx_lis;									// Temporary variable to compare lis's index for a while.

	for (int i = N - 1; i >= 0; i--)							// To trace the index in lis.
		if (trace[i].first == idx_trace)						// [trace의 index와 lis의 index가 같을 경우.]
		{															// [조건에 적합.]
			stk.push(trace[i].second);					// [Trace memory에서 해당되는 값만 extract.]
			idx_trace--;
		}

	while (!stk.empty())
	{
		visit[stk.top()] = false;								// [Stack에 쌓인 index를 false로 변경해준다.]
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
		visit[idx] = true;									// [Cable이 연결된 index는 true로 설정. true일 경우, 나중에 제거해야 하는 cable이 되는 것.]
	}

	sort(arr.begin(), arr.end());						// Sort by index.

	LIS();														//	Do LIS algorithm.

	for (int i = 0; i <= 500000; i++)
		if (visit[i])											// If it has true value, it should be deleted.
			printf("%d\n", i);							// Output of cable index.	
}